/* cidr2mask()
 * arguments:
 * 	cidr: int representing number of bits to mask off in netmask
 *            ex: 192.168.0.1/24, cidr == 24, netmask == 0xFFFFFF00 
 * calls:
 * 	none
 * returns:
 *	netmask: unsigned long int containing the netmask
 *	if(cidr<=1 || cidr >=32) return -1;
 *      -1 is equal to 0xFFFFFFFF
 * notes:
 *      1) declare a 32bit value called mask
 *      2) check to make sure that cidr is a value from 1 to 32
 *      3) if cidr is invalid, return -1
 *      4) loop from 1st bit to last
 *      5) during the loop, increment mask if bit <= cidr
 *      6) during the loop, perform a bitwise left shift
 *      7) return mask 
 */
unsigned long int cidr2mask(int cidr);
