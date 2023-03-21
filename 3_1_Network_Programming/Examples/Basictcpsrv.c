#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#define PORT 9001

int main()
{
	int srvSd, clntSd;
	struct sockaddr_in srvAddr, clntAddr;
	int clntAddrLen, readLen;
	char rBuff[BUFSIZ];
	char wBuff[] = "I am 20 years old.";
	
	
	srvSd = socket(AF_INET, SOCK_STREAM, 0);
	if(srvSd == -1)
	{
		printf("Socket Error\n");
		return -1;
	}	
	memset(&srvAddr, 0, sizeof(srvAddr));
	srvAddr.sin_family = AF_INET;
	srvAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	srvAddr.sin_port = htons(PORT);
	if(bind(srvSd, (struct sockaddr *) &srvAddr, sizeof(srvAddr)) == -1)
	{
		printf("Bind Error");
		return -1;
	}
	if(listen(srvSd, 5) == -1)
	{
		printf("Listen Error");
		return -1;	
	}
	clntAddrLen = sizeof(clntAddr);
	clntSd = accept(srvSd, (struct sockaddr*)&clntAddr, &clntAddrLen);
	if(clntSd == -1)
	{
		printf("Accept Error");
		return -1;
	}
	
	readLen = read(clntSd, rBuff, sizeof(rBuff)-1);
	if(readLen == -1) 
	{
		printf("Read Error");
		return -1;
	}
	rBuff[readLen] = '\0';
	printf("Client: %s \n", rBuff);
	
	
	write(clntSd, wBuff, sizeof(wBuff));
	close(clntSd);
	close(srvSd);	
	
	return 0;	
}