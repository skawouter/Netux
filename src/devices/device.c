#include "../include/device.h"
#include "../include/pci.h"
#include "../include/irq.h"
#include "../include/ata.h"

void init_devices(void){
	init_pci();
	init_ata();
}
