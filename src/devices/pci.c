#include "../include/pci.h"
#include "../include/console.h"
#include "../include/irq.h"
#include "../include/device.h"
void init_pci(void){
	write("do pci stuff");
	short x,y,t;
    char macaddr[8];
	unsigned long inp;
	unsigned long dev;
    unsigned long temp;
    unsigned long iobase;
//devstruct detected;
	for (x=0; x < 128; x++){
		for (y=0; y <16; y++){
			inp  = pci_readword(x,y,0,0);
			if (inp < 65535){
				write("pci device detected");
				dev = pci_readword(x,y,0,1);
                switch (inp){
                    case 0X000010ec: //vendor id for realtek
                        write("realtek device found");
                        switch(dev){
                            case 0xFFFF8139: //device id RLT8139 network card
                                for (t=8; t <= 14; t++){ 
                                    //base addresses from 8 til 14
                                    iobase = pci_readword(x,y,0,t);
                                    if ((iobase & 0x1) == 0x1){ 
                                        //iobase ends with 1
                                        iobase = iobase & 0XFFFFFFF0;
                                        //chop the 1 and reserved field off
                                        char i;
                                        for (i = 0; i < 6; i++)
                                        //first 6 bytes is the mac address
                                        {
                                            macaddr[i] = inb(iobase + i);
                                            writehex(macaddr[i]);
                                        }
                                        write("power on");
                                        outb(iobase + 0x52, 0); //should power on the device
                                        write("reset register");
                                        outb(iobase + 0x37, 0x10); // should clear the registers
                                        char still_reset = 0;
                                        while(inb(iobase + 0x37) & 0x10){
                                            write("waiting for reset :)");
                                        }
                                        write("done");
                                        break;
                                    }
                                }
                      //          write("8139 network card found");
                               break;
                            default:
                                write("unknown card found");
                        }
                        break;
                    default:
                        write("unknown vender");
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
              (lfunc << 8) | (offset << 1) | ((unsigned int)0x80000000));
    /* write out the address */
    outl (0xCF8, address);
    /* read in the data */
    tmp = (unsigned int)(inl (0xCFC));
    return (tmp);
   }
