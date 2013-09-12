#include "../include/pci.h"
#include "../include/console.h"
typedef struct pcicfg {
        uint16  vendor_id;
        uint16  device_id;
        uint16  cmd_reg;
        uint16  status_reg;
        uint8   progif;
        uint8   subclass;
        uint8   class_code;
        uint8   header_type;
        uint32  bar0;
        uint32  bar1;
        uint32  bar2;
        uint32  bar3;
        uint32  bar4;
        uint32  bar5;
        uint16  sub_vendor_id;
        uint16  sub_id;
        uint8   int_line;
        uint8   int_pin;
}

void init_hd(uint32 bus, uint32 dev, uint32 func);
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
						if ( class = 0x01 && subclass = 0x1) {
							init_hd(bus, dev, func)
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
void init_hd(uint32 bus, uint32 dev, uint32 func){
	uint32 bar0, bar1, bar2, bar3, bar4;

}
