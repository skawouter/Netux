#include "console.h"
#include "irq.h"

regs *irq_handler(regs *r) {
    regs *new_regs = r;
    write("received this irq:");
	writenumber((unsigned int) r->int_no);

    //handler = irq_routines[r->int_no - 32];
    //if (handler)
    //    handler(r);
        
    if (r->int_no == 0x20) {  	// INT 0x20, IRQ0, timer interrupt
    
	}
	// this says to the pics that we're done with their interrupt
	// EOI to slave controller
    if (r->int_no >= 40)
    {
        asm volatile("outb %0,%1"::"a"(0xA0), "Nd" (0x20));
	}
    // EOI to master
    asm volatile("outb %0,%1"::"a"(0x20), "Nd" (0x20));

    return new_regs;
}


void outb(short param1, char param2){
 	asm volatile("outb %0,%1" : : "a"(param2), "Nd" (param1));
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
