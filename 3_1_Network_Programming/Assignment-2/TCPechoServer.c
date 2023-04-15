#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

void errProc(const char*);
int main(int argc, char** argv)
{
	int mySock,readLen, nRecv, res, yourSock;
	char buff[BUFSIZ];
	char * strAddr;
	struct sockaddr_in srcAddr, destAddr;
	socklen_t addrLen;

	if(argc != 2) {
		fprintf(stderr,"Usage: %s Port",argv[0]);
		return 0;  
	}	
	mySock = socket(AF_INET, SOCK_STREAM, 0);
	if(mySock == -1) errProc("socket");	
	memset(&srcAddr, 0, sizeof(srcAddr));
	srcAddr.sin_addr.s_addr = htonl(INADDR_ANY);	
	srcAddr.sin_family = AF_INET;
	srcAddr.sin_port = htons(atoi(argv[1]));

	res = bind(mySock,(struct sockaddr *) &srcAddr, sizeof(srcAddr));	
	if(res == -1) errProc("bind");

	if(listen(mySock, 5) < 0) errProc("listen");

	addrLen = sizeof(destAddr);

	while(1)
	{
		yourSock = accept(mySock, (struct sockaddr *)&destAddr, addrLen);
		if(yourSock == -1) errProc("accept");
		
		nRecv = read(yourSock, buff, BUFSIZ-1);
		if(nRecv == -1) errProc("recvfrom");
		if(nRecv > 0) buff[nRecv-1]='\0';
		else buff[nRecv] = '\0';
		strAddr = inet_ntoa(destAddr.sin_addr);
		printf("%s:%d>%s\n",strAddr,ntohs(destAddr.sin_port),buff);
		nRecv = strlen(buff);	
		sendto(mySock, buff, nRecv, 0, 
			(struct sockaddr *) &destAddr, addrLen);		
	}
        close(mySock);	
	return 0;
}

void errProc(const char* str)
{
	fprintf(stderr,"%s: %s \n", str, strerror(errno));
	exit(1);
}
