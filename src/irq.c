#include "console.h"
#include "irq.h"

regs *irq_handler(regs *r) {
    regs *new_regs = r;
    write("received this irq:");
	writenumber((unsigned int) r->int_no);

    /*handler = irq_routines[r->int_no - 32];
    if (handler)
        handler(r);
        
    if (r->int_no == 0x20) {  	// INT 0x20, IRQ0, timer interrupt
    	new_regs = schedule(r);
    	tss[1] = (uint32_t) (new_regs + 1);	// set esp0 in TSS
    	//tss[1] = new_regs->esp;
    	//tss[2] = new_regs->ss;
	}
	*/
	// EOI to slave controller
    if (r->int_no >= 40)
    {
        asm volatile("outb %0,%1"::"a"(0xA0), "Nd" (0x20));
	}
    // EOI to master
    asm volatile("outb %0,%1"::"a"(0x20), "Nd" (0x20));
    
    return new_regs;
}
