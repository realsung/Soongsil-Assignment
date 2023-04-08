#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>


void errorProc(const char*);
int main(int argc, char** argv)
{
	int mySock,readLen, nSent;
	char buff[BUFSIZ];
	struct sockaddr_in destAddr;
	socklen_t addrLen;
	
	mySock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	
	memset(&destAddr, 0, sizeof(destAddr));	
	destAddr.sin_addr.s_addr = inet_addr(argv[1]);	
	destAddr.sin_family = AF_INET;
	destAddr.sin_port = htons(atoi(argv[2]));
	addrLen = sizeof(destAddr);
	while(1)
	{
		fgets(buff, BUFSIZ-1, stdin);
 		readLen = strlen(buff);
		nSent = sendto(mySock, buff, readLen, 0,
			(struct sockaddr *) &destAddr,
			addrLen);
		printf("%d bytes were sent. \n",nSent);		
	}	

	close(mySock);
	return 0;
}

void errProc(const char* str)
{
	fprintf(stderr,"%s: %s \n", str, strerror(errno));
	exit(1);
}
