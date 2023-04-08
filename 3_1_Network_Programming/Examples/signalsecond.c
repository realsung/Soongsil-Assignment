

#include <stdio.h>
#include <signal.h>

int main(int argc, char **argv)
{
	int i = 5;
	struct sigaction new_action, old_action;

	new_action.sa_handler = SIG_IGN;
	sigemptyset(&new_action.sa_mask);
	new_action.sa_flags = 0;

	sigaction(SIGINT, &new_action, &old_action);

	while(1)
	{
		printf("%d: sleep and awake \n", i--);
		sleep(1);
		if(i == 0) break;
	}
	return 1;
}
