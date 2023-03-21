#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORT 9001

int main()		
{		
	int clntSd;	
	struct sockaddr_in clntAddr;	
	int clntAddrLen, readLen;	
	char wBuff[] = "How old are you?";	
	char rBuff[BUFSIZ];	

	clntSd = socket(PF_INET, SOCK_STREAM, 0);	
	if(clntSd == -1)	
	{	
		printf("Socket Creation Error");
		return -1;
	}	
	clntAddr.sin_family = AF_INET;	
	clntAddr.sin_addr.s_addr = inet_addr("127.0.0.1");	
	clntAddr.sin_port = htons(PORT);	
		
	if(connect(clntSd, (struct sockaddr *) &clntAddr, sizeof(clntAddr)) == -1)
	{	
		printf("Connect Error");
		close(clntSd);
		return -1;
	}
	// ssize_t send(int sockfd, const void *buf, size_t len, int flags);
	send(clntSd, wBuff, strlen(wBuff), 0); // write 대신 send 사용
	printf("Client: %s\n",wBuff);	
		
	readLen = read(clntSd, rBuff, sizeof(rBuff)-1);	
	if(readLen == -1)	
	{	
		printf("Read Error");
		return -1;
	}	
	rBuff[readLen] = '\0';
	printf("Server: %s\n", rBuff);
	close(clntSd);
	return 0;
}	
