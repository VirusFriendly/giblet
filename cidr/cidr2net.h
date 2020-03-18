#include <netinet/in.h>

// structure to hold an IP address and it's netmask
struct __netaddr{
  struct in_addr addr;
  struct in_addr mask;
};

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

int cidr2net(char *cidr, struct __netaddr *netaddr);
