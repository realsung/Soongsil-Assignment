#include <stdio.h>
#include <netdb.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
void errProc(const char *);
int main(int argc, char **argv)
{
		 struct hostent *ent;
		 	 struct in_addr **res;
			 	 int i = 0;
				 	 if(argc != 2)
						 	 {
								 	        fprintf(stderr,"Usage: %s <hostname> \n", argv[0]);
												        return -1;
															 }
					 	
					 	ent = gethostbyname(argv[1]);
							if(ent == NULL) errProc("gethostbyname");
									
								res = (struct in_addr **)ent->h_addr_list;
									printf("hostname: %s \n",ent->h_name);
										while(res[i] != NULL)
												{
															printf("%s ", inet_ntoa(*res[i]));
																	i++;
																		}
											printf("\n");
													
}
	
void errProc(const char *str)
{
		fprintf(stderr,"%s: %s\n",str,strerror(errno));
			exit(errno);
}

