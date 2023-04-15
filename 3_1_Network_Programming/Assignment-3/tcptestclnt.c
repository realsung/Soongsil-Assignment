#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>

void err_proc();
int main(int argc, char** argv)
{
	int clntSd;
	struct sockaddr_in clntAddr;
	int clntAddrLen, readLen, recvByte, maxBuff;
	char wBuff[BUFSIZ];
	char rBuff[BUFSIZ];
	if(argc != 3) {
		printf("Usage: %s [IP Address] [Port]\n", argv[0]);
	
	}
	clntSd = socket(AF_INET, SOCK_STREAM, 0);
	if(clntSd == -1) err_proc();
	printf("==== client program =====\n");

	memset(&clntAddr, 0, sizeof(clntAddr));
	clntAddr.sin_family = AF_INET;
	clntAddr.sin_addr.s_addr = inet_addr(argv[1]);
	clntAddr.sin_port = htons(atoi(argv[2]));

	if(connect(clntSd, (struct sockaddr *) &clntAddr,
			    sizeof(clntAddr)) == -1)
	{
		close(clntSd);
		err_proc();	
	}

	while(1){
		fgets(wBuff, BUFSIZ-1, stdin);
		readLen = strlen(wBuff);
		if(readLen < 2) continue;
		write(clntSd, wBuff, readLen-1);
		wBuff[readLen-1] = '\0';
		if(!strcmp(wBuff, "END")) break;
	}
	printf("END ^^\n");
	close(clntSd);

	return 0;
}

void err_proc()
{
	fprintf(stderr,"Error: %s\n", strerror(errno));
	exit(errno);
} 
