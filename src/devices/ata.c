#include "../include/irq.h"
#include "../include/ata.h"
#include "../include/console.h"

void ata_soft_reset(struct ata_dev *dev){
	outb(dev->control, 0x04);
	outb(dev->control, 0x00);
}
void ata_io_wait(struct ata_dev *dev){
	int i;
	for (i = 0; i < 4; i ++ ){
		//ATA_REG_ALTSTATUS
		inb(dev->iobus + 0x0C);
	}
}
void ata_init_device(struct ata_dev *dev){
	int i;
	ata_soft_reset(dev);
	//ATA_REG_HDDEVSEL
	outb(dev->iobus + 0x06, 0XA0 | dev->slave << 4);
	ata_io_wait(dev);

	//ATA_REG_LBA1
	unsigned char c1 = inb(dev->iobus + 0x04);
	//ATA_REG_LBA2
	unsigned char ch = inb(dev->iobus + 0x05);
	if (c1 == 0xFF && ch == 0xFF) {
		write("NO ATA FOUND");
		return;
	}
	write("INIT ATA DEVICE");
	if (c1 == 0x00 && ch == 0x00) {
		outb(dev->iobus + 1, 1);
		outb(dev->control , 0);
		outb(dev->iobus + 0x06, 0xA0 | dev->slave << 4);
		ata_io_wait(dev);
		//ATA_REG_COMMAND + IDENTIFY
		outb(dev->iobus + 0x07, 0xEC);
		ata_io_wait(dev);
		//ATA_REG_COMMAND
		unsigned char status = inb(dev->iobus + 0x07);
		write ("STATUS");
		writehex(status);
		unsigned short int *buf = (unsigned short int *)&dev->identity;

		for (i = 0; i < 256; i++){
			buf[i] = ins(dev->iobus);
		}
		unsigned char *ptr = (unsigned char * )&dev->identity.model;
		for (i = 0; i < 39; i+=2) {
			unsigned char tmp = ptr[i+1];
			ptr[i+1] = ptr[i];
			ptr[i] = tmp;
		}
		write("MODEL");
		write(dev->identity.model);
		write("Sectors 48");
		writenumber((unsigned long int) dev->identity.sectors_48);

		write("Sectors 24");
		writenumber( dev->identity.sectors_28);
		//ATA_REG_CONTROL
		outb(dev->iobus + 0x0C, 0);

	}
}

void init_ata(){
	write("INIT ATA");
	//test ata
	clearconsole(0);
	ata_init_device(&primary_master);
	ata_init_device(&primary_slave);
	ata_init_device(&secondary_master);
	ata_init_device(&secondary_slave);
}
