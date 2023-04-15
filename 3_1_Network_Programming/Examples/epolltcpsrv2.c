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
#include <fcntl.h>

#define MAX_EVENTS	10
void errProc(const char *);
int makeNbSocket(int);

int main(int argc, char** argv)
{
	int listenSd, connectSd;
	struct sockaddr_in srvAddr, clntAddr;
	int clntAddrLen, readLen;
	char rBuff[BUFSIZ];
	int i, completed = 0;

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
	makeNbSocket(listenSd);
	if(listen(listenSd, 5) < 0) errProc("listen");
	
	ev.events = EPOLLIN | EPOLLET;
	ev.data.fd = listenSd;
	if(epoll_ctl(epfd, EPOLL_CTL_ADD, listenSd, &ev) == -1)
		errProc("epoll_ctl");

	clntAddrLen = sizeof(clntAddr);
	while(1)
	{
		printf("Monitoring ... \n");
		ready = epoll_wait(epfd, events, MAX_EVENTS, -1);
		if(ready == -1) 
		{
			if(errno == EINTR)	continue;
			else errProc("epoll_wait");
		}
		
		for(i=0; i<ready; i++)
		{
			if(events[i].data.fd == listenSd) // accept a client 
			{
				while(1)
				{
					connectSd = accept(listenSd, (struct sockaddr *) &clntAddr, &clntAddrLen);
					if(connectSd == -1)
					{
						if((errno == EAGAIN) || (errno == EWOULDBLOCK))
							break;
						else {
							fprintf(stderr,"Accept Error");
							continue;
						}
					}
					fprintf(stderr,"A client is connected...\n");
					
					makeNbSocket(connectSd);					
					ev.data.fd = connectSd;
					ev.events = EPOLLIN | EPOLLET;
					if(epoll_ctl(epfd, EPOLL_CTL_ADD, connectSd, &ev) == -1)
						errProc("epoll_ctl");					
					
				}
				//fprintf(stderr,"There is no client in the queue...\n");
				continue;
			}
			else //IO
			{
				completed = 0;
				while(1)
				{
					readfd = events[i].data.fd;
					readLen = read(readfd, rBuff, sizeof(rBuff));
					if(readLen == -1)
					{
						if(errno != EAGAIN) 
						{
							fprintf(stderr,"Read Error \n");
							completed = 1;
						}
						printf("data unavailable\n");
						break;

					}
					if(readLen == 0) 
					{
						printf("A client is disconnected...\n");
						if(epoll_ctl(epfd, EPOLL_CTL_DEL, readfd, &ev) == -1)
							errProc("epoll_ctl");
						close(events[i].data.fd);
						
					}
					write(1, rBuff, readLen);	
					printf("\n");

					
					//break;
				}

				
			}
		}	
	}
	close(listenSd);
	close(epfd);
	return 0;
}

void errProc(const char* str)
{
	fprintf(stderr,"%s: %s", str, strerror(errno));
	exit(errno);
}

int makeNbSocket(int socket)
{	
  int res;

  res = fcntl(socket, F_GETFL, 0);
  if (res == -1) errProc("fcntl");
  res |= O_NONBLOCK;
  res = fcntl(socket, F_SETFL, res);
  if (res == -1) errProc("fcntl");
  
  return 0;

}
