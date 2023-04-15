#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/epoll.h>
#include <errno.h>

#define MAX_EVENTS	10

void errProc(const char*);

int main(int argc, char** argv)
{
	int listenSd, connectSd;
	struct sockaddr_in srvAddr, clntAddr;
	int clntAddrLen, readLen;
	char rBuff[BUFSIZ];
	int i;

	int epfd, ready, readfd;
	struct epoll_event ev;
	struct epoll_event events[MAX_EVENTS];

	if(argc != 2)
	{
		printf("Usage: %s [Port Number]\n", argv[0]);
		return -1;
	}

	printf("Server start...\n");

	epfd = epoll_create(1);
	if(epfd == -1) errProc("epoll_create");

	listenSd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(listenSd == -1 ) errProc("socket");
	
	memset(&srvAddr, 0, sizeof(srvAddr));
	srvAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	srvAddr.sin_family = AF_INET;
	srvAddr.sin_port = htons(atoi(argv[1]));

	if(bind(listenSd, (struct sockaddr *) &srvAddr, sizeof(srvAddr)) == -1)
		errProc("bind");

	if(listen(listenSd, 5) < 0) errProc("listen");
	

	ev.events = EPOLLIN;
	ev.data.fd = listenSd;
	if(epoll_ctl(epfd, EPOLL_CTL_ADD, listenSd, &ev) == -1)
		errProc("epoll_ctl");

	clntAddrLen = sizeof(clntAddr);
	while(1) {
		printf("Monitoring ... \n");
		ready = epoll_wait(epfd, events, MAX_EVENTS, -1);
		if(ready == -1) {
			if(errno == EINTR) continue;
			else errProc("epoll_wait");			
		}
		
		for(i=0; i<ready; i++)	{
			if(events[i].data.fd == listenSd) {// accept a client 
				connectSd = accept(listenSd, (struct sockaddr *) &clntAddr, &clntAddrLen);
				if(connectSd == -1)	{
					fprintf(stderr,"Accept Error");
					continue;
				}
				fprintf(stderr,"A client is connected...\n");
				ev.data.fd = connectSd;
				if(epoll_ctl(epfd, EPOLL_CTL_ADD, connectSd, &ev) == -1)
					errProc("epoll_ctl");				
			}
			else {//IO
				readfd = events[i].data.fd;
				readLen = read(readfd, rBuff, sizeof(rBuff)-1);
				if(readLen == 0) 
				{
					fprintf(stderr,"A client is disconnected...\n");
					if(epoll_ctl(epfd, EPOLL_CTL_DEL, readfd, &ev) == -1)
						errProc("epoll_ctl");	
					close(readfd);
					continue;
				}
				rBuff[readLen] = '\0';
				printf("Client(%d): %s\n", events[i].data.fd,rBuff);
				write(events[i].data.fd, rBuff, strlen(rBuff));
			}
		}	
	}
	close(listenSd);
	close(epfd);
	return 0;
}

void errProc(const char * str)
{
	fprintf(stderr,"%s: %s", str, strerror(errno));
	exit(1);
}