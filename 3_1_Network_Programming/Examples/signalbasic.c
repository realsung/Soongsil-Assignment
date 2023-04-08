
#include <stdio.h>
#include <signal.h>

int global_count = 10;

void sigint_handler(int sig)
{
	if(sig == SIGINT)
	{
		printf("Received SIGINT... %d Lives Left \n", global_count--);
	}
	if(global_count <= 0)
	{
		signal(SIGINT, SIG_DFL);
	}
}

int main(int argc, char **argv)
{
	int i = 0;
	signal(SIGINT, sigint_handler);
	while(1)
	{
		printf("%d: sleep and awake \n", ++i);
		sleep(5);
	}
	return 1;
}
