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
#define MAX_CLIENTS 10

typedef struct {
    SOCKET socket;
    char username[MAX_USERNAME_LENGTH];
    int isConnected;
} Client;

int main() {
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    struct addrinfo *bind_address;
    getaddrinfo(0, "8080", &hints, &bind_address);


    // printf("Creating socket...\n");
    SOCKET socket_listen;
    socket_listen = socket(bind_address->ai_family,
            bind_address->ai_socktype, bind_address->ai_protocol);
    if (!ISVALIDSOCKET(socket_listen)) {
        fprintf(stderr, "socket() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    }

    // printf("Binding socket to local address...\n");
    if (bind(socket_listen,
                bind_address->ai_addr, bind_address->ai_addrlen)) {
        fprintf(stderr, "bind() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    }
    freeaddrinfo(bind_address);


    // printf("Listening...\n");
    if (listen(socket_listen, 10) < 0) {
        fprintf(stderr, "listen() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    }

    fd_set master;
    FD_ZERO(&master);
    FD_SET(socket_listen, &master);
    SOCKET max_socket = socket_listen;

    // printf("Waiting for connections...\n");
    printf(">> Server Started\n");

    Client clients[MAX_CLIENTS];
    memset(clients, 0, sizeof(clients));

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
                    // printf("New connection from %s\n", address_buffer);
                    
                    int client_index = -1;
                    for (int j = 0; j < MAX_CLIENTS; ++j) {
                        if (clients[j].socket == 0) {
                            // Found an available client slot
                            client_index = j;
                            break;
                        }
                    }

                    if (client_index != -1) {
                        clients[client_index].socket = socket_client;
                        snprintf(clients[client_index].username, sizeof(clients[client_index].username), "사용자 %d", client_index + 1);
                        clients[client_index].isConnected = 1;
                        
                        char join_message[100];
                        snprintf(join_message, sizeof(join_message), "%s 님이 입장하셨습니다.\n", clients[client_index].username);
                        for (SOCKET m = 0; m <= MAX_CLIENTS; m++) {
                            if (FD_ISSET(m, &master)) {
                                // if (clients[m].socket != 0) {
                                send(m, join_message, strlen(join_message), MSG_NOSIGNAL);
                                // }
                            }
                        }

                    } else {
                        fprintf(stderr, "Maximum number of clients reached. Connection rejected.\n");
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
                    if (bytes_received < 1) {
                        for (k = 0; k <= max_socket; k++) {
                            if (clients[k].socket == i) {
                                printf("leave user : %s\n", clients[k].username);
                                char leave_message[100];
                                snprintf(leave_message, sizeof(leave_message), "%s 님이 대화방을 나갔습니다.\n", clients[k].username);
                                for(SOCKET m  = 0; m <= MAX_CLIENTS; ++m){
                                    if(FD_ISSET(m, &master)){
                                        if (clients[m].socket != 0) {
                                            send(m, leave_message, strlen(leave_message), MSG_NOSIGNAL);
                                        }
                                    }
                                }
                                break;
                            }
                        }
                        FD_CLR(i, &master);
                        CLOSESOCKET(i);
                        continue;
                    }
                    memset(info, 0, sizeof(info));

                    SOCKET j;
                    for (j = 1; j <= max_socket; ++j) {
                        if (FD_ISSET(j, &master)) {
                            if (j == socket_listen || j == i){
                                time_t ct = time(NULL);
                                struct tm tm = *localtime(&ct);
                                printf("From Client: %s : %s", clients[j].username, read);
                                sprintf(info, "[ %d.%d.%d. %02d:%02d:%02d ] %s : %s", 
                                    tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
                                    tm.tm_hour + 9, tm.tm_min, tm.tm_sec,
                                    clients[j].username, read);
                                send(j, info, strlen(info), MSG_NOSIGNAL);
                                continue;
                            }else{
                                for(k = 0; k <= MAX_CLIENTS; k++){
                                    if(clients[k].socket == socket_listen){
                                        time_t ct = time(NULL);
                                        struct tm tm = *localtime(&ct);
                                        // memset(info, 0, sizeof(info));
                                        printf("From Client: %s : %s", clients[k].username, read);
                                        sprintf(info, "[ %d.%d.%d. %02d:%02d:%02d ] %s : %s", 
                                            tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
                                            tm.tm_hour + 9, tm.tm_min, tm.tm_sec,
                                            clients[k].username, read);
                                        // printf("%s", info);
                                        // send(i, info, strlen(info), 0);
                                        send(j, info, strlen(info), 0);
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            } //if FD_ISSET
        } //for i to max_socket
    } //while(1)

    for (int k = 0; k <= MAX_CLIENTS; k++) {
        if (clients[k].socket != 0) {
            CLOSESOCKET(clients[k].socket);
        }
    }

    printf("Closing listening socket...\n");
    CLOSESOCKET(socket_listen);

    printf("Finished.\n");

    return 0;
}