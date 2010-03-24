#include "console.h"
#include "isr.h"

void isr_handler(registers_t regs)
{
	// the function prints out all our saved registers
	write("received this interrupt:");
	writenumber((unsigned int) regs.int_no);
}