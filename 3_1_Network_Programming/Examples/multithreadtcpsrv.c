#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/wait.h>
#include <pthread.h>

void * client_module(void * data)
{
	char rBuff[BUFSIZ];
	int readLen;
	int connectSd;
	connectSd = *((int *) data);
	while(1)
	{
		readLen = read(connectSd, rBuff, sizeof(rBuff)-1);
		if(readLen <= 0) break;	
		rBuff[readLen] = '\0';
		printf("Client(%d): %s\n",connectSd,rBuff);
		write(connectSd, rBuff, strlen(rBuff));
	}
	fprintf(stderr,"The client is disconnected.\n");
	close(connectSd);
}

int main(int argc, char** argv)
{
	int listenSd, connectSd;
	struct sockaddr_in srvAddr, clntAddr;
	int clntAddrLen, strLen;

	struct sigaction act;
	pthread_t thread;
	
	if(argc != 2)
	{
		printf("Usage: %s [Port Number]\n", argv[0]);
		return -1;
	}

	printf("Server start...\n");
	listenSd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	memset(&srvAddr, 0, sizeof(srvAddr));
	srvAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	srvAddr.sin_family = AF_INET;
	srvAddr.sin_port = htons(atoi(argv[1]));

	bind(listenSd, (struct sockaddr *) &srvAddr, sizeof(srvAddr));
	listen(listenSd, 5);
	
	clntAddrLen = sizeof(clntAddr);
	while(1)
	{
		connectSd = accept(listenSd,
			   	(struct sockaddr *) &clntAddr, &clntAddrLen);
		if(connectSd == -1)
		{
			continue;
		}
		else
		{
			printf("A client is connected...\n");
		}	

		pthread_create(&thread, NULL, client_module, (void *) &connectSd);
		pthread_detach(thread);
	}
	close(listenSd);
	return 0;
}
