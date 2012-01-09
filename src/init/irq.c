#include "../include/console.h"
#include "../include/irq.h"
#include "../include/keyb.h"
regs *irq_handler(regs *r) {
    regs *new_regs = r;

	//handle irqs if they are registered :)
    if (irqlist[r->int_no].irq != 0){
		(*irqlist[r->int_no].functpoint)();
	} else {
        if (r->int_no != 0x21 && r->int_no != 0x20){
            write("irq received but not registered");
            writehex(r->int_no);
        }
        
    }
    if (r->int_no >= 0x28)
    {

		outb(0x20,0x20);
		outb(0x20,0xA0);
	}else{
		outb(0x20,0x20);
	}
    // EOI to master


    return new_regs;
}

int register_irq(unsigned char irq, int (*functpoint) ())
{
	struct irq_struct irqcurr;
	irqcurr.irq = irq;
	irqcurr.functpoint = functpoint;
	irqlist[irq] = irqcurr;
	return 0;
}
void unregister_irq(unsigned char irq)
{
	irqlist[irq].functpoint = 0;
	irqlist[irq].irq = 0;
}
void init_pic(void){
	// init master PIC
	outb(0x20, 0x11);
	outb(0x21, 0x20); // Interruptnumber for IRQ 0
	outb(0x21, 0x04);
	outb(0x21, 0x01); // ICW 4

	// init Slave PIC
	outb(0xa0, 0x11);
	outb(0xa1, 0x28); // Interruptnumber for IRQ 8
	outb(0xa1, 0x02);
	outb(0xa1, 0x01); // ICW 4


    // activate all IRQs
    outb(0x21, 0x0);
    outb(0xA1, 0x0);
}
