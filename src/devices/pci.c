#include "../include/pci.h"
#include "../include/console.h"
#include "../include/irq.h"
#include "../include/device.h"


typedef unsigned char   uint8;
typedef unsigned short  uint16;
typedef unsigned int    uint32;
typedef unsigned long   uint64;
typedef unsigned long   size_t;
typedef signed char             int8;
typedef signed short    int16;
typedef signed int              int32;
typedef signed long             int64;
/*unsigned short pcirw(int bus, int slot, int fun, int reg, int offset){
	
	outl(0xCF8, (0x80000000| (bus << 16) | (slot << 11 ) | (fun << 8 ) | (reg & ~3)));
	return inl(0xCFC);
}*/
/*void init_pci(void){
	write("do pci stuff");
	short x,y,k;
    char macaddr[8];
	unsigned long inp;
	unsigned long dev;
    unsigned long temp;
    unsigned long iobase;
    unsigned long inters;
//devstruct detected;
	for (x=0; x < 128; x++){
		for (y=0; y <32; y++){
			inp  = pci_readword(x,y,0,0);
			if (inp != 0xffff){
				write("pci device detected");
				for (k=0; k<8; k++){
					dev = pci_readword(x,y,k,0);
					if ( dev != 0xffff) {
						write("vendor detected");
						writehex(dev);
						int  vendor;
						int device; 
						device = pci_readword(x,y,k,2);
						writehex(device);
						return;
					}
				}
			}
		}
	}
}*/
/*void pci_write_conf32(uint8 bus, uint8 dev, uint8 func, uint8 reg, uint32 val)
{
        uint32 port = (0x80000000U)|(bus<<16)|(dev<<11)|(func<<8)|(reg);

        outportl(0xcf8, port);
        outportl(0xcfc, val);
}*/
/*
void pci_write_conf16(uint8 bus, uint8 dev, uint8 func, uint8 reg, uint16 val)
{
        uint32 port = (0x80000000U)|(bus<<16)|(dev<<11)|(func<<8)|(reg);

        outportl(0xcf8, port);
        outportw((uint16)(0xcfc + (reg&2)), val);
}*/

/*uint32 pci_read_conf32(uint8 bus, uint8 dev, uint8 func, uint8 reg)
{
        uint32 ret;
        uint32 port = (0x80000000U)|(bus<<16)|(dev<<11)|(func<<8)|(reg);

        outportl(0xcf8, port);

        ret = inportl(0xcfc);
        return ret;
}*/
uint8 inportb (unsigned short _port)
{
        uint8 rv = 0;
        __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
       return rv;
}

uint16 inportw (unsigned short _port)
{
        uint16 rv = 0;
        __asm__ __volatile__ ("inw %1, %0" : "=a" (rv) : "dN" (_port));
        return rv;
}


uint16 pci_read_conf16(uint8 bus, uint8 dev, uint8 func, uint8 reg)
{
        uint16 ret;
        uint32 port = (0x80000000U)|(bus<<16)|(dev<<11)|(func<<8)|(reg);

        outl(0xcf8, port);

        ret = inportw((uint16)(0xcfc + (reg&2)));
        return ret;
}

uint8 pci_read_conf8(uint8 bus, uint8 dev, uint8 func, uint8 reg)
{
        uint8 ret;
        uint32 port = (0x80000000U)|(bus<<16)|(dev<<11)|(func<<8)|(reg);

        outl(0xcf8, port);

        ret = inportb((uint16)(0xcfc + (reg&3)));
        return ret;
}

#define PCI_VENDOR_ID		0x0
#define PCI_DEVICE_ID		0x2
#define PCI_CLASS_CODE		0xB
#define PCI_SUBCLASS_CODE	0xA
#define PCI_PROG_IF		0x9
#define PCI_REV_ID		0x8
#define PCI_SUB_ID		0x2e
#define PCI_SUBVEND_ID		0x2c
#define PCI_HEADER_TYPE		0xe

void init_pci(void){
	write("pci init probing");
	int dev, bus, func;
	uint16 vend, device;
	uint32 class, subclass, prog, rev_id, subsys, subsysvend, header;
	for (bus = 0; bus < 256; bus ++){
		for (dev = 0; dev < 256; dev ++){
			vend = pci_read_conf16(bus, dev, 0, PCI_VENDOR_ID);
			if (vend != 0xffff){
				for (func = 0; func < 256; func ++){
					vend = pci_read_conf16(bus,dev,func,PCI_VENDOR_ID);
					if (vend == 0xffff) {
						func = 256;
						continue;
					}
					device = pci_read_conf16(bus,dev,func,PCI_DEVICE_ID);
					if (device == 0xffff) {
						func = 256 ;
						continue;
					}
					if (vend == 0x10ec){
						write("Realtek");
						continue;
					}
					if (vend == 0x1013){
						write("Cirrus Logic Video");
						continue;
					}
					class = pci_read_conf8(bus, dev, func, PCI_CLASS_CODE);
					subclass = pci_read_conf8(bus, dev, func, PCI_SUBCLASS_CODE+1);
					if (vend == 0x8086) {
						write("Intel");
						writehex(device);
						write("class - subclass");
						writehex(class);
						writehex(subclass);
						continue;
					}
					if (vend == 0x1AF4) {
						write("Virtio");
						writehex(device);
						write("class - subclass");
						writehex(class);
						writehex(subclass);
						continue;
					}

					write("DEVICE FOUND");
					prog = pci_read_conf8(bus, dev, func, PCI_PROG_IF);
					rev_id = pci_read_conf8(bus, dev, func, PCI_REV_ID);

					subsys = pci_read_conf8(bus, dev, func, PCI_SUB_ID);
					subsysvend = pci_read_conf8(bus, dev, func, PCI_SUBVEND_ID);
					header = pci_read_conf8(bus, dev, func, PCI_REV_ID);
					write("class - subclass");
					writehex(class);
					writehex(subclass);
				}
			}
		}
	}
}

unsigned long pci_readword(unsigned short bus,unsigned short slot,unsigned short func,unsigned short offset){
   unsigned long address;
   unsigned long lbus = (unsigned long)bus;
   unsigned long lslot = (unsigned long)slot;
   unsigned long lfunc = (unsigned long)func;

   /* create configuration address as per Figure 1 */
   address = (unsigned long)((lbus << 16) | (lslot << 11) |
             (lfunc << 8) | (offset & 0xfc) | ((unsigned long)0x80000000));

   outl(0xcf8, address);
   /* write out the address */
   return (unsigned short)((inl (0xCFC) >> ((offset & 2) * 8)) & 0xffff);
}
