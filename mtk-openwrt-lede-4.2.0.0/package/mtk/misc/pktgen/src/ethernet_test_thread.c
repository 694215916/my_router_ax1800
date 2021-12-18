#include <fcntl.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
//#include <pthread.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define MIN_PAYLOAD	(46)
#define MAX_PAYLOAD	(4000)
#define ETH_TYPE	0x8888

//#define DBG

int fd;
int done = 0;
struct sockaddr_ll addr;
unsigned long pkt_sent = 0;
unsigned long payload_len = 0;
unsigned long curr_payload_len = MIN_PAYLOAD;
unsigned long curr_payload_len2 = MAX_PAYLOAD;
unsigned char pattern = 0;
unsigned long remain_pkt_cnt = 0;
unsigned char continue_tx = 0;
unsigned char finish_send = 0;
unsigned char smac_list[6] = {0x00, 0x12, 0x34, 0x56, 0x78, 0xAB};
unsigned char dmac_list[6] = {0x00, 0x30, 0x00, 0x00, 0x00, 0x01};
unsigned long delay = 0;

void usage(char *argv[])
{
	printf("Usage: %s [pkt_cnt] [payload_len] [payload_pattern] [interface] [delay-interval]\n", argv[0]);
	printf("	pkt_cnt = 0: infinite \n");
	printf("	        > 0: how many packets you want to transmit \n");
	printf("	payload_len: frame length [%d~%d (0=random, 1=incremental, 2=decremental)]\n", MIN_PAYLOAD, MAX_PAYLOAD);
	printf("	payload_pattern: payload content [0x00~0xFF (0x00=random)]\n");
	printf("	interface:eth2/eth3\n");
	printf("	delay-interval:0~10000000 us\n");
	printf("\n");
	printf("    6     6      2       %d-%d       \n",  MIN_PAYLOAD, MAX_PAYLOAD);
	printf(" +-----+------+---------+----------++\n");
	printf(" |  DA |  SA  |ETH_TYPE |Payload  |\n");
	printf(" +-----+------+---------+---------++\n");
	printf("Ex: ether_test 1 0 0 eth2 10\n");
	printf("    -> 1 pkts, payload_len=random, pattern=random, eth3, delay=10us\n");

}

/*
 * Sometimes the TX and RX packet format are different.
 * That's why I used two structure for TX and RX 
 */


struct tx_pkt_s {
	
	struct tx_hdr_s {
		unsigned char da[6];
		unsigned char sa[6];
		unsigned short eth_type;
	} __attribute__ ((packed)) hdr;

        unsigned long payload_len; /* packet len without header */
	unsigned char pattern;
	unsigned char payload[MAX_PAYLOAD];

} __attribute__ ((packed));

#define MAC_HDR_LEN sizeof(struct mac_frame_hdr)
#define TX_HDR_LEN sizeof(struct tx_hdr_s)

#define RX_HDR_LEN sizeof(struct rx_hdr_s)


/**
 * @brief dump rx/tx frame header
 *
 * @param pkt
 * @param dir
 */
void dump_tx_header(struct tx_pkt_s *pkt)
{
	printf("======TX=========\n");
	printf("DA=%02X:%02X:%02X:%02X:%02X:%02X\n",pkt->hdr.da[0],pkt->hdr.da[1],pkt->hdr.da[2],pkt->hdr.da[3],pkt->hdr.da[4],pkt->hdr.da[5]);
	printf("SA=%02X:%02X:%02X:%02X:%02X:%02X\n",pkt->hdr.sa[0],pkt->hdr.sa[1],pkt->hdr.sa[2],pkt->hdr.sa[3],pkt->hdr.sa[4],pkt->hdr.sa[5]);
	printf("ETH_TYPE=%x\n",pkt->hdr.eth_type);
}

/**
 * @brief create test packet
 *
 * @param pkt
 *
 * @return 
 */
int create_pkt(struct tx_pkt_s *pkt)
{
	int i = 0;


	//decide DA mac header
	memcpy(pkt->hdr.da, dmac_list, 6);

	//decide SA mac header
	memcpy(pkt->hdr.sa, smac_list, 6);

	//decide Eth Type here
	pkt->hdr.eth_type= ETH_TYPE;

	//decide packet len here
	if (payload_len == 0) {
	    pkt->payload_len = rand() % MAX_PAYLOAD;
	    if (pkt->payload_len < MIN_PAYLOAD) {
		pkt->payload_len = MIN_PAYLOAD;
	    }
	}else if(payload_len==1) {
	    pkt->payload_len = curr_payload_len++ % MAX_PAYLOAD;
	    if (pkt->payload_len < MIN_PAYLOAD) {
		pkt->payload_len = MIN_PAYLOAD;
	    }
	}else if(payload_len==2) {
	    //pkt->hdr.payload_len = curr_payload_len2--;
	    pkt->payload_len = curr_payload_len2--;
	    if (curr_payload_len2 == MIN_PAYLOAD) {
		curr_payload_len2 = MAX_PAYLOAD;
	    }
	}else {
	    //pkt->hdr.payload_len = payload_len;
	    pkt->payload_len = payload_len;
	}

	//decide test pattern here (0x00~0xFF)
	if (pattern == 0x00) {
	    pkt->pattern = rand() & 0xFF;
	    if (pkt->pattern == 0) {
		pkt->pattern=1;
	    }
	}else {
	    pkt->pattern = pattern;
	}


	for (i=0; i < pkt->payload_len; i++) {
	    pkt->payload[i] = pkt->pattern;
	}
       
	return 1;
}

int create_random_pkt(struct tx_pkt_s *pkt)
{
	int i = 0;

	//decide packet len here
	if (payload_len == 0) {
	    pkt->payload_len = rand() % MAX_PAYLOAD;
	    if (pkt->payload_len < MIN_PAYLOAD) {
		pkt->payload_len = MIN_PAYLOAD;
	    }
	}
	//decide test pattern here (0x00~0xFF)
	if (pattern == 0x00) {
	    pkt->pattern = rand() & 0xFF;
	}else {
	    pkt->pattern = pattern;
	}

	if (pattern == 0x00) {
		for (i=0; i< pkt->payload_len; i++) {
		       if ((i % 3) == 0)
				pkt->payload[i] = (pkt->pattern + i + i ) & 0xFF;
		       else
				pkt->payload[i] = (pkt->pattern + i + 0x23 ) & 0xFF;
		}
	}else {
		for (i=0; i < pkt->payload_len; i++) {
			pkt->payload[i] = pkt->pattern;
		}
	}

       
	return 1;
}



void send_pkt()
{
	struct tx_pkt_s send_pkt;

	create_pkt(&send_pkt);
	do
	{
		if (delay != 0)
			usleep(delay);
		
			/* stop by CTRL + C */
		if (done == 1) {
			break;
		}
		/* TX */	
		create_random_pkt(&send_pkt);
		if ( sendto(fd, &send_pkt, (send_pkt.payload_len + TX_HDR_LEN), 0, (struct sockaddr *)&addr, sizeof(struct sockaddr_ll)) > 0 ) {
		    pkt_sent++;
		}
		else
		    printf("sendto fail \n");

	}while(continue_tx == 1 || --remain_pkt_cnt != 0);

	printf("send %d packets OK\n", pkt_sent);
	finish_send = 1;
}

/**
 * @brief main function
 *
 * @return 
 */
int main(int argc, char *argv[])
{
	//pthread_t		id;
	int			ret = 0;
	struct ifreq ifr;

	if (argc < 4) {
		usage(argv);
		exit(1);
	}
	
	remain_pkt_cnt = strtoul(argv[1], NULL ,10);

	if (remain_pkt_cnt == 0) {
	    continue_tx = 1;
	}

	payload_len = strtoul(argv[2], NULL ,10);
	pattern = strtoul(argv[3], NULL ,16);
	delay = strtoul(argv[5], NULL ,10);
	printf("pkt_cnt=%d payload_len=%d pattern=%x \n",remain_pkt_cnt, payload_len, pattern);

	if (payload_len > MAX_PAYLOAD) {
		printf("payload length is over %d\n", MAX_PAYLOAD);
		exit(1);
	}
	fd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if ( fd < 0 )
	{
		perror("socket");
		return -1;
	}



	memset(&ifr, 0, sizeof(ifr));




	//strcpy (ifr.ifr_name, ETH3_IFNAME);
	strcpy (ifr.ifr_name, argv[4]);
	printf("send to %s\n", ifr.ifr_name);

	if (ioctl(fd, SIOCGIFINDEX, &ifr) == -1) {
	    printf("%s not exist\n", ifr.ifr_name);
	    close(fd);
	    return -1;
	}


	ioctl(fd, SIOCGIFFLAGS, &ifr);
	if ( (ifr.ifr_flags & IFF_UP) == 0) {
	    printf("%s is down\n", ifr.ifr_name);
	    close(fd);
	    return -1;
	}

	ioctl(fd, SIOCGIFINDEX, &ifr);

	/* create socket */
	bzero(&addr, sizeof(addr));
	addr.sll_family = PF_PACKET;
	addr.sll_protocol = htons(ETH_P_ALL);
	addr.sll_ifindex = ifr.ifr_ifindex; /* by input */
//	addr.sll_ifindex = 2; /* eth2 */
	addr.sll_pkttype = PACKET_OTHERHOST;


	if ( fcntl(fd, F_SETFL, O_NONBLOCK) != 0 )
		perror("Request nonblocking I/O");


	srand(time(NULL));
	//ret=pthread_create(&id, NULL, (void *) send_pkt, NULL);
        send_pkt();

	if (ret != 0) {
		printf("create pthread error!\n");
		exit(1);
	}

	close(fd);
			
	return 0;
}

