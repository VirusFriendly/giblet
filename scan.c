/* perform an arp request for each address in list (A) */
int scan_up();

/* perform an arp request for each non responcive address from a
 * 	responcive address */
int scan_lim();

/* perform an arp request for each non responcive address from a non
 * 	responcive address */
int scan_non();

/* perform an arp request from address1 to address2 */
int arp(address1, address2);

/* get address to use */
int get_addr(void);
