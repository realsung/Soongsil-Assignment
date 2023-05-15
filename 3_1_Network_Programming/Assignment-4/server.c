#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define ISVALIDSOCKET(s) ((s) >= 0)
#define CLOSESOCKET(s) close(s)
#define SOCKET int
#define GETSOCKETERRNO() (errno)
#define MAX_USERNAME_LENGTH 20
#define MAX_CLIENTS 10 // 만약 클라이언트 최대 할당 개수 늘릴거면 이거 늘리면됨.

// Client 구조체 선언 (클라이언트 식별용)
typedef struct {
    SOCKET socket; // 소켓 번호
    char username[MAX_USERNAME_LENGTH]; // 클라이언트 이름 e.g. 사용자1, 사용자2, ...
} Client;

int main() {
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    // 서버 기본 세팅 
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    // 8080 포트 할당
    struct addrinfo *bind_address;
    getaddrinfo(0, "8080", &hints, &bind_address);

    // 소켓 할당
    SOCKET socket_listen;
    socket_listen = socket(bind_address->ai_family,
            bind_address->ai_socktype, bind_address->ai_protocol);
    if (!ISVALIDSOCKET(socket_listen)) {
        fprintf(stderr, "socket() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    }

    // 소켓 바인딩
    if (bind(socket_listen,
                bind_address->ai_addr, bind_address->ai_addrlen)) {
        fprintf(stderr, "bind() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    }
    freeaddrinfo(bind_address);

    // 클라이언트 listen
    if (listen(socket_listen, 10) < 0) {
        fprintf(stderr, "listen() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    }

    // select 쓰기 위해 소켓 초기화
    fd_set master;
    FD_ZERO(&master);
    FD_SET(socket_listen, &master);
    SOCKET max_socket = socket_listen;

    printf(">> Server Started\n");

    Client clients[MAX_CLIENTS]; // 클라이언트 선언
    for(int s = 0; s <= MAX_CLIENTS; s++){ // 클라이언트 구조체 초기화
        clients[s].socket = 0;
        memset(clients[s].username, 0, sizeof(clients[s].username));
    }

    while(1) {
        fd_set reads;
        reads = master;
        if (select(max_socket+1, &reads, 0, 0, 0) < 0) {
            fprintf(stderr, "select() failed. (%d)\n", GETSOCKETERRNO());
            return 1;
        }

        SOCKET i;
        for(i = 1; i <= max_socket; ++i) {
            if (FD_ISSET(i, &reads)) {
                // 클라이언트 연결이 되면
                if (i == socket_listen) {
                    struct sockaddr_storage client_address;
                    socklen_t client_len = sizeof(client_address);
                    SOCKET socket_client = accept(socket_listen,
                            (struct sockaddr*) &client_address,
                            &client_len);
                    if (!ISVALIDSOCKET(socket_client)) {
                        fprintf(stderr, "accept() failed. (%d)\n",
                                GETSOCKETERRNO());
                        return 1;
                    }

                    FD_SET(socket_client, &master);
                    if (socket_client > max_socket)
                        max_socket = socket_client;

                    char address_buffer[100];
                    getnameinfo((struct sockaddr*)&client_address,
                            client_len,
                            address_buffer, sizeof(address_buffer), 0, 0,
                            NI_NUMERICHOST);
                    
                    // 클라이언트 인덱스 할당
                    int client_index = -1;
                    for (int j = 0; j <= MAX_CLIENTS; ++j) {
                        if (clients[j].socket == 0) { //client.socket == -1이면 이전에 연결됐던 인덱스임 / 0이면 남는 곳
                            client_index = j;
                            break;
                        }
                    }

                    if (client_index != -1) {
                        // 사용자명 할당
                        clients[client_index].socket = socket_client;
                        snprintf(clients[client_index].username, sizeof(clients[client_index].username), "사용자 %d", client_index + 1);
                        
                        char join_message[100];
                        memset(join_message, 0, sizeof(join_message));
                        // 입장 메시지 할당
                        snprintf(join_message, sizeof(join_message), "%s 님이 입장하셨습니다.\n", clients[client_index].username);

                        // FD_ISSET된 클라이언트들에게 join_message 출력
                        for (SOCKET m = 0; m <= MAX_CLIENTS; m++) {
                            if (FD_ISSET(m, &master)) {
                                // if (clients[m].socket != 0) {
                                send(m, join_message, strlen(join_message), MSG_NOSIGNAL);
                                // }
                            }
                        }
                    } else {
                        fprintf(stderr, "채팅방에 인원수가 다 찼습니다.\n");
                        CLOSESOCKET(socket_client);
                    }
                    
                    printf(">> Accept connection from client\n");

                } else {
                    char read[1024];
                    char info[1100];
                    int k;

                    memset(read, 0, sizeof(read));
                    memset(info, 0, sizeof(info));
                    int bytes_received = recv(i, read, 1024, 0);
                    
                    // 연결이 끊겼을 경우 처리
                    if (bytes_received < 1) {
                        for(k = 0; k <= MAX_CLIENTS; k++){
                            // 연결 끊긴 해당 socket 가져오기
                            if(clients[k].socket == i){
                                printf("leave user : %s\n", clients[k].username);
                                // socket -1 처리
                                clients[k].socket = -1;
                                // 퇴장 메시지 할당
                                char leave_message[100];
                                memset(leave_message, 0, sizeof(leave_message));
                                snprintf(leave_message, sizeof(leave_message), "%s 님이 대화방을 나갔습니다.\n", clients[k].username);
                                // FD_ISSET된 클라이언트들에게 leave_message 출력
                                for(int m1 = 0; m1 <= MAX_CLIENTS; m1++){
                                    if(FD_ISSET(m1, &master)){
                                        send(m1, leave_message, strlen(leave_message), MSG_NOSIGNAL);
                                    }
                                }
                                // client의 name 초기화
                                memset(clients[k].username, 0, sizeof(MAX_USERNAME_LENGTH));
                                break;
                            }
                        }
                        // 해당 소켓 정리
                        FD_CLR(i, &master);
                        CLOSESOCKET(i);
                        continue;
                    }

                    // 클라이언트가 메시지를 전송할 때
                    SOCKET j;
                    for (j = 1; j <= max_socket; ++j) {
                        if (FD_ISSET(j, &master)) {
                            if (j == socket_listen || j == i){  // 클라이언트 자기 자신
                                for(k = 0; k <= MAX_CLIENTS; k++){
                                    if(clients[k].socket == j){ 
                                        // 전송 시간 가져오기
                                        time_t ct = time(NULL);
                                        struct tm tm = *localtime(&ct);
                                        printf("From Client: %s : %s", clients[k].username, read);
                                        // 전송시간, 사용자식별정보, 보낸 메시지 send
                                        sprintf(info, "[ %d.%d.%d. %02d:%02d:%02d ] %s : %s", 
                                            tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
                                            tm.tm_hour + 9, tm.tm_min, tm.tm_sec,
                                            clients[k].username, read);
                                        send(j, info, strlen(info), MSG_NOSIGNAL);

                                        // 보낸 사용자 ID 이용해서 해당 ID와 데이터 값들을 자기 클라이언트 제외 다른 클라이언트들에게 전송
                                        for(int k1 = 0; k1 <= MAX_CLIENTS; k1++){ // 다른 클라이언트들에게 전송
                                            // memset(info, 0, sizeof(info));
                                            if(clients[k1].socket != 0 && clients[k1].socket != j){ // socket이 할당이 되지 않은경우와 자기 자신인 경우 제외
                                                // sprintf(info, "-[ %d.%d.%d. %02d:%02d:%02d ] %s : %s", 
                                                // tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
                                                // tm.tm_hour + 9, tm.tm_min, tm.tm_sec,
                                                // clients[k].username, read);
                                                send(clients[k1].socket, info, strlen(info), MSG_NOSIGNAL); // 타 클아이언트들에게 전송
                                            }
                                        }
                                    }
                                }
                            }
                            // test code not use.
                            // else{ 
                                // for(k = 0; k <= MAX_CLIENTS; k++){
                                //     if(clients[k].socket != 0 && clients[k].socket != j){
                                //         time_t ct = time(NULL);
                                //         struct tm tm = *localtime(&ct);
                                //         // memset(info, 0, sizeof(info));
                                //         // printf("From Client: %s : %s", clients[k].username, read);
                                //         sprintf(info, "-[ %d.%d.%d. %02d:%02d:%02d ] %s : %s", 
                                //             tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
                                //             tm.tm_hour + 9, tm.tm_min, tm.tm_sec,
                                //             clients[send_socket].username, read);
                                //         // printf("%s", info);
                                //         // send(i, info, strlen(info), 0);
                                //         send(j, info, strlen(info), 0);
                                //         // break;
                                //     }
                                // }
                            // }
                        }
                    }
                }
            }
        }
    }

    // 소켓 정리
    for (int k = 0; k <= MAX_CLIENTS; k++) {
        if (clients[k].socket != 0) {
            CLOSESOCKET(clients[k].socket);
        }
    }

    CLOSESOCKET(socket_listen);

    return 0;
}