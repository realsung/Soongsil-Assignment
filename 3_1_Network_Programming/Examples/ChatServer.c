#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define MAX_CLIENT 10

void errProc(const char*);
int checkSockList(struct sockaddr_in *entry, struct sockaddr_in *list, int count);

int main(int argc, char** argv)
{
	int mySock,readLen, nRecv, res;
	char buff[BUFSIZ];
	char nameBuff[50];
	char * strAddr;
	struct sockaddr_in srcAddr, destAddr;
	socklen_t addrLen;
	int nClient = 0, i = 0, port;
	struct sockaddr_in sockets[MAX_CLIENT];
	
	if(argc != 2) {
		fprintf(stderr,"Usage: %s Port",argv[0]);
		return 0;  
	}	

	memset(&sockets, 0, sizeof(sockets[0])*MAX_CLIENT);
	mySock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(mySock == -1) errProc("socket");	
	
	memset(&srcAddr, 0, sizeof(srcAddr));
	srcAddr.sin_addr.s_addr = htonl(INADDR_ANY);	
	srcAddr.sin_family = AF_INET;
	srcAddr.sin_port = htons(atoi(argv[1]));

	res = bind(mySock,(struct sockaddr *) &srcAddr,	sizeof(srcAddr));	
	if(res == -1) errProc("bind");
	addrLen = sizeof(destAddr);
		
	while(1)
	{
		nRecv = recvfrom(mySock, buff, BUFSIZ-1 , 0,
			(struct sockaddr *) &destAddr,
			&addrLen);
		if(nRecv == -1) errProc("recvfrom");
		res = checkSockList(&destAddr, sockets, nClient);

		if(res == nClient) { /*New Client*/
			if(res == MAX_CLIENT) continue; /*MAX Client Limit*/
			else 
			{
				memcpy(&sockets[res], &destAddr, sizeof(destAddr));
				nClient++;
			}
		}		
		printf("nClient: %d \n", nClient);
		strAddr = inet_ntoa(destAddr.sin_addr);
		sprintf(nameBuff, "%s: %d>> ", strAddr, ntohs(destAddr.sin_port));
		
		for(i = 0; i < nClient; i++) 
		{
			if(i == res) continue; /* sender == receiver skip */
			sendto(mySock, nameBuff, strlen(nameBuff), 0, 
			(struct sockaddr *) &sockets[i], addrLen);
			sendto(mySock, buff, nRecv, 0, 
			(struct sockaddr *) &sockets[i], addrLen);
		}		
	}		
	return 0;
}

/* 리스트 검색 후 인덱스 반환, 
리스트에 엔트리가 없을 경우 마지막 인덱스 + 1 반환 */
int checkSockList(struct sockaddr_in *entry, 
					struct sockaddr_in *list, int count)
{
	int i = 0;
	struct sockaddr_in *ptrSockAddr;
	for(i = 0; i < count; i++) {
		ptrSockAddr = list + i;
		if(memcmp(ptrSockAddr, entry, 
			sizeof(struct sockaddr_in)) == 0)
			return i;
	}
	return i;
} 


void errProc(const char* str)
{
	fprintf(stderr,"%s: %s \n", str, strerror(errno));
	exit(1);
}
