#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <net/ethernet.h>
#include "list.h"

struct hostlist {
	struct in_addr ip;
	char ha[ETH_ALEN];
	char name[12];
};	

unsigned long int cidr_mask(int);
List *mkiplist(char *);

List *mkiplist(char *bucket) {
	int cidr=0;
	int ipaddr_32bit=0;
	unsigned long int netsize=0;
	unsigned long int netmask=0;
	unsigned long int netaddr=0;
	unsigned long int netbcast=0;
	char *ip_addr=NULL;
	char *val=NULL;
	int i=0;
	struct hostlist *host=NULL;
	List *data=NULL;
	List *list=NULL;
	int datasize=sizeof(struct hostlist)+sizeof(List);

	if(bucket == NULL) {
		return NULL;
	}

	val = strsep(&bucket, "/");
	cidr = atoi(strsep(&bucket, "/"));
	ipaddr_32bit = htonl(inet_addr(val));

	netmask=cidr_mask(cidr);
	netaddr=ipaddr_32bit&netmask;
	netsize=netmask^0xffffffff;
	netbcast=ipaddr_32bit|netsize;

	for(i=1;i<netsize;i++) {
		data=(List *) malloc(datasize);
		host=(struct hostlist *) data+1;
		(host->ip).s_addr=htonl(netaddr+i);
		ip_addr=inet_ntoa(host->ip);
		strncpy(host->name, ip_addr, 12);
		data->name=host->name;
		add_to_list(&list, data);
	}

	return 0;
}

unsigned long int cidr_mask(int bits) {
	unsigned long int netmask=0;
	int i;
	
	if(bits >= 32) {
		return -1;
	}
	
	for(i=0;i<=bits;i++) {
		netmask++;
		netmask<<=1;
	}

	netmask<<=(31-bits);
	return netmask;
}

void *hostinfo(void) {
	struct ifreq argp;
	
	ioctl(socket, SIOCGIFHWADDR, (char *) &argp);
}
