#include "device.h"
#include "irq.h"
#define PCI_VENDOR_ID           0x0
#define PCI_DEVICE_ID           0x2
#define PCI_CLASS_CODE          0xB
#define PCI_SUBCLASS_CODE       0xA
#define PCI_PROG_IF             0x9
#define PCI_REV_ID              0x8
#define PCI_SUB_ID              0x2e
#define PCI_SUBVEND_ID          0x2c
#define PCI_HEADER_TYPE         0xe

#define PCI_BAR_0               0x10
#define PCI_BAR(x)      (PCI_BAR_0+((x)*0x4))
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

uint32 pci_read_conf32(uint8 bus, uint8 dev, uint8 func, uint8 reg)
{
        uint32 ret;
        uint32 port = (0x80000000U)|(bus<<16)|(dev<<11)|(func<<8)|(reg);

        outportl(0xcf8, port);

        ret = inportl(0xcfc);
        return ret;
}


void init_pci(void);
