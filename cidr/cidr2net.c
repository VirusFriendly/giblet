#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "cidr2mask.h"
#include "cidr2net.h"

/* structure to hold an IP address and it's netmask(defined int cidr2net.h):
 * struct __netaddr{
 * struct in_addr addr;
 * struct in_addr mask;
 * };
 */

/* cidr2net()
 * arguments:
 * 	cidr: string containing an IP in cidr notation. eg: 192.168.0.1/24
 *      netaddr: pointer to __netaddr struct to put our IP and netmask in 
 * calls:
 *      atoi(), cidr2mask(), inet_aton(), fprintf(), htonl()
 * returns:
 *	1 on success
 *      0 on failure
 * notes:
 *      1) put ip portion of cidr into ipstr
 *      2) check to see if next char is '/' if not, bail
 *      3) skip '/"
 *      4) convert prefix part of cidr string to an int
 *      5) call cidr2mask to get netmask, place result in our address struct
 *      6) call inet_aton to convert ipstr to integer and put in our struct
 *      7) convert IP in our address structure to network byte order
 *      8) return 1 if all went well up to this point
 */

int cidr2net(char *cidr, struct __netaddr *netaddr)
{
  
  int i;
  char ipstr[16];  // big enough to hold the longest ip and '\0'
  uint32_t prefix; // ipaddr/prefix - 192.168.1.40/24

  /* copy IP portion into ipstr one char at a time until you hit the '/' */
  for(i=0; i<16 && cidr[i]!='/' && cidr[i]!='\0'; ++i){
    ipstr[i] = cidr[i];
  }ipstr[i]='\0';

  /* after IP is read next char should be '/' if it isn't, theres a problem. */
  if(cidr[i] != '/'){
    fprintf(stderr, "cidr2net(): Invalid IP. Must be in format: 192.168.0.1/24\n");
    return 1;
  }

  ++i; // skip the '/'

  prefix = atoi(cidr+i); // convert cidr prefix portion to int
  /* get netmask for specified prefix and put in our address structure */
  netaddr->mask.s_addr = cidr2mask(prefix);

  /* convert ip string to integer & put into our address structure */
  /* return  with error 0 on fail */
  if(!inet_aton(ipstr, &(netaddr->addr))){
    fprintf(stderr, "cidr2net(): error converting IP address.\n");
    return 0;
  }
  /* convert to network byte order */
  netaddr->addr.s_addr = htonl(netaddr->addr.s_addr);

  return 1;
}
