#include <stdio.h>
#include <string.h>
#include "cidr2mask.h"
#include "cidr2net.h"

int main(int argc, char **argv)
{
  int ret;
  char cidr[19]="192.168.1.0/24";
  struct __netaddr address;
  address.addr.s_addr=0;
  address.mask.s_addr=0;

  if(argc == 2){
    strncpy(cidr, argv[1], sizeof cidr);
  }

  if((ret = cidr2net(cidr, &address))){ //returns 1 on success, 0 on failure
  printf("IP address/cidr:\t %s\n", cidr);
  printf("IP address(hex):\t %x\n", address.addr.s_addr);
  printf("Network Mask(hex):\t %x\n", address.mask.s_addr);
  }

  return(ret);
}
