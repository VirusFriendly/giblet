#include <features.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>
#include <net/if_arp.h>
#include <sys/socket.h>
#include <sys/types.h>

struct iparp {
	ar_sha[ETH_ALEN];
	ar_sip[4];
	ar_tha[ETH_ALEN];
	ar_tip[4];
};

#define DATASIZE sizeof(struct arphdr)+sizeof(struct iparp)

int arp(void *ethhdr) {
	int stype=0;
	int s=0;

	if(*ethhdr == NULL) {
		stype=SOCK_DGRAM;
	} else {
		stype=SOCK_RAW;
	}
	
	s=socket(PF_PACKET, stype, ETHERTYPE_ARP);
	whereis(s);
	send(s, arp, ARPSIZE, 0);
	isat(s);
}

void *whereis(struct xxxx *info, char *data) {
	struct arphdr *arh=data;
	struct iparp *ard=data+sizeof(struct arphdr);
	
	arh->ar_op=ARPOP_REQUEST;
	arh->ar_hrd=ARPHRD_ETHER;
	arh->ar_pro=0x800;
	arh->ar_hln=ETH_ALEN;
	arh->ar_pln=4;
	memcpy(ard->ar_sha, info->my_ha, ETH_ALEN);
	memcpy(ard->ar_tha, info->ta_ha, ETH_ALEN);
	memcpy(ard->ar_sip, info->my_ip, 4);
	memcpy(ard->ar_tip. info->ta_ip, 4);

	return 0;
}

int isat(int socket) {
}

int getife(char *ifname, struct ifreq &ifr) {
	ioctl(skfd, SIOCGIFFLAGS, ifr);
	ioctl(skfd, SIOCGIFADDR, &ifr);
}
