#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <arpa/inet.h>


void errProc(const char*);
int main(int argc, char** argv)
{
	int mySock,readLen, nSent, nRecv;
	char buff[BUFSIZ];
	char strAddr;
	struct sockaddr_in destAddr, destAddr2;
	socklen_t addrLen;	
	
	mySock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	
	memset(&destAddr, 0, sizeof(destAddr));	
	destAddr.sin_addr.s_addr = inet_addr(argv[1]);	
	destAddr.sin_family = AF_INET;
	destAddr.sin_port = htons(atoi(argv[2]));

	memset(&destAddr2, 0, sizeof(destAddr2));
	destAddr2.sin_addr.s_addr = inet_addr(argv[1]);	
	destAddr2.sin_family = AF_INET;
	destAddr2.sin_port = htons(9050);
	addrLen = sizeof(destAddr2);	

	connect(mySock, (struct sockaddr*) &destAddr,
		sizeof(destAddr));
	while(1)
	{
		// connected UDP
		fgets(buff, BUFSIZ-1, stdin);
 		readLen = strlen(buff);
		nSent = write(mySock, buff, readLen);
		if(nSent == -1) errProc("write");
		printf("%d bytes were sent. \n",nSent);		

		nRecv = read(mySock, buff, BUFSIZ-1);
		if(nRecv == -1) errProc("read");
		buff[nRecv] = '\0';
		printf("Server: %s\n", buff);

		// sendto 
		fgets(buff, BUFSIZ-1, stdin);
 		readLen = strlen(buff);
		nSent = sendto(mySock, buff, readLen, 0,
			(struct sockaddr *) &destAddr2, addrLen);
		if(nSent == -1) errProc("write");
		printf("%d bytes were sent. \n",nSent);		
	
		nRecv = recvfrom(mySock, buff, BUFSIZ-1, 0,
			(struct sockaddr *) &destAddr2, &addrLen);
		if(nRecv == -1) errProc("read");
		buff[nRecv] = '\0';
		strAddr = inet_ntoa(destAddr2.sin_addr);
		printf("%s:%d >%s\n",strAddr,
			ntohs(destAddr2.sin_port), buff);

	}
	close(mySock);	
	return 0;
}

void errProc(const char* str)
{
	fprintf(stderr,"%s: %s \n", str, strerror(errno));
	exit(1);
}
