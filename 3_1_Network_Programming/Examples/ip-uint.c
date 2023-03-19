#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char** argv)
{
	uint32_t ipInInt;
	uint32_t ipInInt2;

	
	char *ipInStr = "127.0.0.1";
	ipInInt = inet_network(ipInStr);


	printf("String: %s, Decimal: %u, Hex: %X \n",
			 ipInStr, ipInInt, ipInInt);
	
	ipInInt = htonl(ipInInt);
	printf("After htonl - Decimal: %u, Hex: %X \n", 
			ipInInt, ipInInt);


	ipInInt2 = inet_addr(ipInStr);
	printf("after inet_addr: %u, Hex: %x \n", ipInInt2, ipInInt2);
	
	return 0;
}

