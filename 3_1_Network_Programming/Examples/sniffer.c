#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/types.h> //uintx_t
#include <errno.h>

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

struct pseudo_hdr
{
	uint32_t src;
	uint32_t dst;
	uint8_t zeros;
	uint8_t proto;
	uint16_t len;
};

void errProc(const char*);
uint16_t checksum(const void *ptr, int len);
void parseTcpHeader(struct tcp_hdr * myHdr);

int main(int argc, char ** argv)
{
	int socketSd;
	int fromAddrLen;
	char rBuff[BUFSIZ];

	struct tcp_hdr *myTcp;
	struct ip_hdr *myIp;

	struct sockaddr_in fromAddr;
	
	if((socketSd = socket(PF_INET, SOCK_RAW, IPPROTO_TCP)) < 0)
		errProc("socket");
	
	while(1) 
	{	
		if(recvfrom(socketSd, rBuff, BUFSIZ-1, 0x0, (struct sockaddr *)&fromAddr, &fromAddrLen) < 0)
				errProc("Recv Error");

		myIp = (struct ip_hdr *) rBuff;
		myTcp = (struct tcp_hdr *) (rBuff + sizeof(struct ip_hdr));
		parseTcpHeader(myTcp);
	}	

	close(socketSd);

	return 0;
}

void parseTcpHeader(struct tcp_hdr * myHdr)
{
	printf("============Recv TCP Segment ===========\n");
	printf("Source Port: %d\n",ntohs(myHdr->tcp_src));
	printf("Destination Port: %d\n",ntohs(myHdr->tcp_dst));
	printf("Sequence No.t: %d\n",ntohs(myHdr->tcp_seq));
	printf("ACK No.: %d\n",ntohs(myHdr->tcp_ackno));
	printf("Flags: %c%c%c%c%c%c\n",(myHdr->tcp_fin?'F':'X'),
		(myHdr->tcp_syn?'S':'X'),(myHdr->tcp_rst?'R':'X'),(myHdr->tcp_psh?'P':'X'),
		(myHdr->tcp_ack?'A':'X'),(myHdr->tcp_urg?'U':'X'));
	printf("Checksum: %X\n",ntohs(myHdr->tcp_check));	
}


void errProc(const char* str)
{
	fprintf(stderr,"%s: %s \n", str, strerror(errno));
	exit(1);
}


uint16_t checksum(const void *ptr, int len)
{
    int sum = 0;
    uint16_t answer = 0;
    uint16_t *w = (uint16_t *) ptr;
    int nleft = len;
 
    while(nleft > 1){
        sum += *w++;
        nleft -= 2;
    }
 
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    answer = ~sum;
    return(answer);
}