#include <stdio.h>
#include <fcntl.h>
//#include <stdlib.h>

int main(int argc, char** argv) {
	int fD, writeLen, readLen;
	char rBuff[BUFSIZ];
	if(argc != 2) {
		fprintf(stderr, "Usage: %s [Filename] \n ",argv[0]);
		return 0;
	}
	
	readLen = read(0, rBuff, BUFSIZ-1);
	if(readLen == -1)
	{
		fprintf(stderr, "Read Error \n");
		return 0;
	}
	printf("Total reading data: %d\n", readLen);
	rBuff[readLen] = '\0';		
	fD = open(argv[1],O_WRONLY|O_CREAT|O_TRUNC);
	if(fD == -1)
	{
		fprintf(stderr, "Open Error \n");
		return 0;
	}

	writeLen = write(fD, rBuff, readLen+1);
	if(writeLen == -1)
	{
		fprintf(stderr, "Write Error \n");
		return 0;
	}
	printf("Total writing data: %d\n", readLen);	
	close(fD);
	return 0;
}
