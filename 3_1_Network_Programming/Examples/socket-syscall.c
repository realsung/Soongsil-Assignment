#include <sys/socket.h>
#include <stdio.h>
#include <fcntl.h>

int main()
{
	int sD1, fD1, sD2, fD2;

	sD1 = socket(PF_INET, SOCK_STREAM, 0);
	fD1 = open("test",O_RDONLY);
	sD2 = socket(PF_INET, SOCK_STREAM, 0);
	fD2 = open("test",O_RDONLY);
	
	printf("sD1:%d, fD1:%d, sD2:%d, fD2:%d \n",sD1, fD1, sD2, fD2);
	
	close(sD1);
	close(fD1);
	close(sD2);
	close(fD1);


	
	return 0;
}
