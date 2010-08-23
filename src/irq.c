#include "console.h"
#include "irq.h"
#include "keyb.h"
regs *irq_handler(regs *r) {
    regs *new_regs = r;
   

    //handler = irq_routines[r->int_no - 32];
    //if (handler)
    //    handler(r);
        
    if (r->int_no == 0x20) {  	// INT 0x20, IRQ0, timer interrupt
    
	}
	if (r->int_no == 0x21) {
		short test;
		test = inb(0x60);
		keyb_handle(test);
	}
	
	// this says to the pics that we're done with their interrupt
	// EOI to slave controller
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
