#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFSIZE 1024

int main() {
    int sockfd, newsockfd, portno, clilen, n;
    char buffer[BUFSIZE];
    struct sockaddr_in serv_addr, cli_addr;
    FILE *fp;
    struct stat st;
    char *file_buffer;
    size_t file_size;
    char http_header[BUFSIZE];

    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        printf("socket error");

    memset((char *) &serv_addr, 0, sizeof(serv_addr));
    portno = PORT;

    // 서버 주소 및 포트 할당
    // memset으로 serv_addr 값 초기화하고 서버 초기값 세팅을 한다.
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET; // IPv4
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = PORT; // 포트 번호

    // 서버 소켓 바인드
    // socketfd에 서버 초기값 세팅 정보를 할당해준다. IP, PORT 등
    if(bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1){
        printf("Bind Error");
        return -1;
    }
   
    // 서버 listen
    // Client 연결 대기
    listen(sockfd, 5);

    // 클라이언트 요청 accept
    // 클라이언트 연결이 되면 소켓을 새로 할당(newsockfd)
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &clilen);
    if(newsockfd == -1){
        printf("Accept Error");
        return -1;
    }

    // 클라이언트 패킷 수신
    memset(buffer, 0, BUFSIZE);
    n = read(newsockfd, buffer, BUFSIZE);
    if (n < 0) 
        printf("ERROR reading from socket");

    // 파일 오픈
    // fopen으로 image.jpg를 읽어온다.
    fp = fopen("image.jpg", "r");

    // 파일 크기 확인 (stat 함수 사용 하여 st 구조체에 저장, 파일 크기는 file_size 변수에 저장)
    if(stat("image.jpg", &st) == -1){
        printf("Stat Error");
        return -1;
    }

    // off_t st_size; /*total size, in byte*/
    // stat.st_size에 파일 크기가 저장된다.
    file_size = st.st_size;

    // 파일 버퍼 동적 할당 (malloc)
    // 파일을 읽기 위해 동적할당 받는다. file_buffer는 heap영역을 할당된 가르킨다.
    file_buffer = malloc(file_size);

    // 파일 읽기
    // fread를 이용해서 동적할당한 file_buffer에 image.jpg 내용을 읽어온다.
    fread(file_buffer, file_size, 1, fp);

    // http header 만들기
    sprintf(http_header, "HTTP/1.1 200 OK\r\n"
            "Content-Type: image/jpeg\r\n"
            "Content-Length: %ld\r\n"
            "Connection: close\r\n"
            "\r\n", file_size);

    // http header 전송
    // send 이용해서 http_header 먼저 전송한다.
    send(newsockfd, http_header, strlen(http_header), 0);

    // http body 전송
    // header 전송했으니, image.jpg 읽어온 file_buffer를 전송한다.
    send(newsockfd, file_buffer, file_size, 0);

    // 사용한 소켓, 파일포인터, 동적할당 메모리 등은 해제한다)
    fclose(fp);
    free(file_buffer);

    close(newsockfd);
    close(sockfd);

    return 0;
}
