#include "../include/pci.h"
#include "../include/console.h"
#include "../include/irq.h"

void init_pci(void){
	write("do pci stuff");
	int x,y;
	long inp;
	short vend;
	for (x=0; x < 128; x++){
		for (y=0; y <16; y++){
			inp  = pci_readword(x,y,0,0);
			if (inp < 65535){
				write("found one");
				vend = pci_readword(x,y,0,2);
				writenumber(vend);
			}
					
		}
		
	}	
}


unsigned long pci_readword(unsigned short bus,unsigned short slot,unsigned short function,unsigned short offset){
	
	unsigned long address;
    unsigned long lbus = (unsigned long)bus;
    unsigned long lslot = (unsigned long)slot;
    unsigned long lfunc = (unsigned long)function;
    unsigned short tmp = 0;
 
    /* create configuration address as per Figure 1 */
    address = (unsigned long)((lbus << 16) | (lslot << 11) |
              (lfunc << 8) | (offset & 0xfc) | ((unsigned int)0x80000000));
 
    /* write out the address */
    outl (0xCF8, address);
    /* read in the data */
    tmp = (unsigned short)((inl (0xCFC) >> ((offset & 2) * 8)) & 0xffff);
    return (tmp);
   }
