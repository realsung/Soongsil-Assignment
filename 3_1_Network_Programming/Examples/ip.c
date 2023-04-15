#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/types.h> //uintx_t

#define SPORT 90
#define DPORT 90
#define IP_ADDRESS "127.0.0.1"


struct ip_hdr
{
#if __BYTE_ORDER__ == __LITTLE_ENDIAN 
	uint8_t ip_hdr_len:4; //(IP Header Length)
	uint8_t ip_version:4; //(IP Version)
#else
	uint8_t ip_version:4;
	uint8_t ip_hdr_len:4;
#endif
	uint8_t ip_tos; // (TOS Field)
	uint16_t ip_len; // (Payload Field= header + SDU)
	
	uint16_t ip_id; // (Identification Field)
	uint16_t ip_off; // (Flag(DF,MF) + Fragment offset Field)
	
	uint8_t ip_ttl; // (Time to Live)
	uint8_t ip_proto; // (Upper Layer Protocol)
	uint16_t ip_check; // (IP Checksum)

	uint32_t ip_src; //(Source Address)

	uint32_t ip_dst; //(Destination Address)
};

struct tcp_hdr
{
	uint16_t tcp_src; //(Source Port)
	uint16_t tcp_dst; //(Destination Port)

	uint32_t tcp_seq; //(Sequence Number Field)

	uint32_t tcp_ackno; //(Acknowledgment Number Field)

#if __BYTE_ORDER__ == __LITTLE_ENDIAN
	uint8_t tcp_rsv1:4; //(Reserved 4bits)
	uint8_t tcp_hdr_len:4;//(Header Length)
	uint8_t tcp_fin:1;//(6bit flags = U/A/P/R/S/F)
	uint8_t tcp_syn:1;
	uint8_t tcp_rst:1;
	uint8_t tcp_psh:1;
	uint8_t tcp_ack:1;
	uint8_t tcp_urg:1;
	uint8_t tcp_rsv2:2;//(Reserved 2bits)
#else
	uint8_t tcp_hdr_len:4;
	uint8_t tcp_rsv1:4; //(Reserved 4bit)
	uint8_t tcp_rsv2:2; //(Reserved 4bit)
	uint8_t tcp_urg:1; //(6bit flags = U/A/P/R/S/F)
	uint8_t tcp_ack:1;
	uint8_t tcp_psh:1;	
	uint8_t tcp_rst:1;	
	uint8_t tcp_syn:1;
	uint8_t tcp_fin:1;	
#endif
	uint16_t tcp_win_size; //(Window Size)
	
	uint16_t tcp_check; //(TCP Checksum)
	uint16_t tcp_urg_ptr; //(Urgent Pointer)
};

struct udp_hdr
{
	uint16_t udp_src; //(Source Port)
	uint16_t udp_dst; //(Destination Port)

	uint16_t udp_len; //(Payload Length: header + SDU)
	uint16_t udp_check; //(UDP Checksum)
};

struct usr_data
{
	uint16_t usr_id;
	uint16_t usr_len;

	uint32_t usr_data;
};



int main(int argc, char ** argv)
{
	int socketSd;
	int sock_opt=1;
	int size_tx_packet = sizeof(struct ip_hdr)+sizeof(struct tcp_hdr)+sizeof(struct usr_data);

	struct ip_hdr *myIp;
	struct tcp_hdr *myTcp;
	struct usr_data *myData;

	struct in_addr srcAddr, destAddr;
	struct sockaddr_in sockAddr;

	char *packet = (char *)malloc(size_tx_packet);

	myIp = (struct ip_hdr *) (packet);
	myTcp = (struct tcp_hdr *) (packet + sizeof(struct ip_hdr));
	myData = (struct usr_data *) (packet + sizeof(struct ip_hdr) + sizeof(struct tcp_hdr));

	if((socketSd = socket(PF_INET, SOCK_RAW, IPPROTO_TCP)) < 0)
	{
		fprintf(stderr, "socket open error\n");
		exit(0);
	}
	
	if(setsockopt(socketSd, IPPROTO_IP, IP_HDRINCL, (char *)&sock_opt, sizeof(sock_opt)) < 0) 
	{
		fprintf(stderr, "setsockopt error\n");
		exit(0);			
	}

	memset(packet, 0, size_tx_packet);

	srcAddr.s_addr = inet_addr(IP_ADDRESS);
	destAddr.s_addr = inet_addr(IP_ADDRESS);

	myData->usr_id = 1;
	myData->usr_len = 16;
	myData->usr_data = 1981;

	myTcp->tcp_src = htons(SPORT);
	myTcp->tcp_dst = htons(DPORT);
	myTcp->tcp_seq = htons(rand()%time(NULL));
	myTcp->tcp_ackno = 0;
	myTcp->tcp_hdr_len = 5;
	myTcp->tcp_rsv1 = 0;
	myTcp->tcp_rsv2 = 0;
	myTcp->tcp_fin = 0;
	myTcp->tcp_syn = 1;
	myTcp->tcp_rst = 0;
	myTcp->tcp_psh = 0;
	myTcp->tcp_ack = 0;
	myTcp->tcp_urg = 0;
	myTcp->tcp_win_size = htons(1024);
	myTcp->tcp_check = 0;
	myTcp->tcp_urg_ptr = 0;

	myIp->ip_hdr_len = 5;
	myIp->ip_version = 4;
	myIp->ip_tos = 0;
	myIp->ip_len = htons(size_tx_packet);
	myIp->ip_id = htons(2);
	myIp->ip_off = 0;
	myIp->ip_ttl = IPDEFTTL;
	myIp->ip_proto = IPPROTO_TCP;
	myIp->ip_src = srcAddr.s_addr;
	myIp->ip_dst = destAddr.s_addr;
	myIp->ip_check = 0x1111;


	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr = destAddr;
	sockAddr.sin_port = htons(DPORT);
	
	if( sendto(socketSd, packet, size_tx_packet, 0x0, (struct sockaddr *)&sockAddr, sizeof(sockAddr)) < 0 )
	{
		fprintf(stderr,"send error \n");
		exit(1);
	}

	close(socketSd);

	return 0;
}

