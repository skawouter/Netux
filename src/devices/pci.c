#include "include/pci.h"
#include "include/console.h"
#include "include/irq.h"

void init_pci(void){
	write("do pci stuff");
	writenumber(pci_readword(0,0,0,0));
	writenumber(pci_readword(1,0,0,0));
	writenumber(pci_readword(1,1,0,0));
	writenumber(pci_readword(1,2,0,0));
	writenumber(pci_readword(1,3,0,0));
	
}


unsigned long pci_readword(unsigned short bus,unsigned short slot,unsigned short function,unsigned short offset){
	
	unsigned long address;
    unsigned long lbus = (unsigned long)bus;
    unsigned long lslot = (unsigned long)slot;
    unsigned long lfunc = (unsigned long)function;
    unsigned short tmp = 0;
 
    /* create configuration address as per Figure 1 */
    address = (unsigned long)((lbus << 16) | (lslot << 11) |
              (lfunc << 8) | (offset << 2) | ((unsigned int)0x80000000));
 
    /* write out the address */
    outl (0xCF8, address);
    /* read in the data */
    tmp = (unsigned short)((inl (0xCFC) >> ((offset & 2) * 8)) & 0xffff);
    return (tmp);
   }
