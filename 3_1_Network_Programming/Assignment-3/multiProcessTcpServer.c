#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void handler(int);
void errProc();
void errPrint();

int main(int argc, char** argv)
{
	int srvSd, clntSd;
	struct sockaddr_in srvAddr, clntAddr;
	int clntAddrLen, readLen, strLen;
	char rBuff[BUFSIZ];
	pid_t pid;
	struct sigaction sa;
	int status;

	if(argc != 2) {
		printf("Usage: %s [port] \n", argv[0]);
		exit(1);
	}
	printf("Server start...\n");
	signal(SIGCHLD, handler); // Child Process에 대한 핸들러 처리

	srvSd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(srvSd == -1 ) errProc();

	memset(&srvAddr, 0, sizeof(srvAddr));
	srvAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	srvAddr.sin_family = AF_INET;
	srvAddr.sin_port = htons(atoi(argv[1]));

	if(bind(srvSd, (struct sockaddr *) &srvAddr, sizeof(srvAddr)) == -1)
		errProc();
	if(listen(srvSd, 5) < 0)
		errProc();
	clntAddrLen = sizeof(clntAddr);
	while(1)
	{
		clntSd = accept(srvSd, (struct sockaddr *)
					 &clntAddr, &clntAddrLen);
		if(clntSd == -1) {
			errPrint();
			continue;	
		}
		printf("client %s:%d is connected...\n",
			inet_ntoa(clntAddr.sin_addr),
			ntohs(clntAddr.sin_port));	
		pid = fork();
		if(pid == 0) { /* child process */
			close(srvSd);
			while(1) {
				readLen = read(clntSd, rBuff, sizeof(rBuff)-1);
				if(readLen == 0) break;
				rBuff[readLen] = '\0';
				printf("Client(%d): %s\n",
					ntohs(clntAddr.sin_port),rBuff);
				write(clntSd, rBuff, strlen(rBuff));
			}
			printf("Client(%d): is disconnected\n",
				ntohs(clntAddr.sin_port));
			close(clntSd);
			return 0;
		}	
		else if(pid == -1) errProc("fork");
		else { /*Parent Process*/
			close(clntSd);
		}	
	}
	close(srvSd);
	return 0;
}

void handler(int sig){
	pid_t pid;
	int status;
	while((pid = wait(&status)) > 0){
		printf("[*] status : %d, %d Child Process Terminated!\n", status, pid);
	}
	// while((pid = waitpid(-1, &status, WNOHANG)) > 0){ // pid가 -1이면 자식 프로세스 기다림
	// 	printf("END\n");
	// }
}

void errProc(const char *str)
{
    fprintf(stderr,"%s: %s \n",str, strerror(errno));
    exit(1);
}

void errPrint(const char *str)
{
	fprintf(stderr,"%s: %s \n",str, strerror(errno));
}
