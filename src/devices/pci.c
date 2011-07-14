#include "../include/pci.h"
#include "../include/console.h"
#include "../include/irq.h"
#include "../include/device.h"
void init_pci(void){
	write("do pci stuff");
	short x,y;
	unsigned long inp;
	unsigned long dev;
//devstruct detected;
	for (x=0; x < 128; x++){
		for (y=0; y <16; y++){
			inp  = pci_readword(x,y,0,0);
			if (inp < 65535){
				write("pci device detected");
				dev = pci_readword(x,y,0,2);
				switch (dev){
					case 0xFFFF8139:
						write("found 8139 network card");
						writetoconsole("vendor: ",0);
						writehex(inp & 0X0000FFFF);
						break;
					default:
						write("unknown device");
				}
			}
					
		}
		
	}
}



unsigned long pci_readword(unsigned short bus,unsigned short slot,unsigned short function,unsigned short offset){
	
	unsigned long address;
    unsigned long lbus = (unsigned long)bus;
    unsigned long lslot = (unsigned long)slot;
    unsigned long lfunc = (unsigned long)function;
    unsigned long tmp = 0;
 
    /* create configuration address as per Figure 1 */
    address = (unsigned int)((lbus << 16) | (lslot << 11) |
              (lfunc << 8) | (offset) | ((unsigned int)0x80000000));
    /* write out the address */
    outl (0xCF8, address);
    /* read in the data */
    tmp = (unsigned int)(inl (0xCFC) );
    return (tmp);
   }
