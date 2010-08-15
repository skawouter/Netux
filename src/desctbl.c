#include "desctbl.h"
#include "console.h"
#include "irq.h"
idt_entry_t idt_entries[256];
idt_ptr_t idt_ptr;
//initializing :)
void init_descriptor_tables()
{
	write("onto the init");
	init_gdt();
	write("gdt init passed");
	//~ clearconsole(0);
	init_idt();
	write("idt init passed");
	return;
}
void init_idt()
{
	idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1;
	write("the size of our entry is ");
	writenumber((unsigned int) sizeof(idt_entry_t));
	idt_ptr.base = (unsigned int)&idt_entries;

	
	write("opening the GATES!");
	writenumber((unsigned int)isr0);
	idt_set_gate(0,(unsigned int)isr0, 0x08, 0x8e);
	idt_set_gate(1,(unsigned int)isr1, 0x08, 0x8e);
	idt_set_gate(2,(unsigned int)isr2, 0x08, 0x8e);
	idt_set_gate(3,(unsigned int)isr3, 0x08, 0x8e);
	idt_set_gate(4,(unsigned int)isr4, 0x08, 0x8e);
	idt_set_gate(5,(unsigned int)isr5, 0x08, 0x8e);
	idt_set_gate(6,(unsigned int)isr6, 0x08, 0x8e);
	idt_set_gate(7,(unsigned int)isr7, 0x08, 0x8e);
	idt_set_gate(8,(unsigned int)isr8, 0x08, 0x8e);
	idt_set_gate(9,(unsigned int)isr9, 0x08, 0x8e);
	idt_set_gate(10,(unsigned int)isr10, 0x08, 0x8e);
	idt_set_gate(11,(unsigned int)isr11, 0x08, 0x8e);
	idt_set_gate(12,(unsigned int)isr12, 0x08, 0x8e);
	idt_set_gate(13,(unsigned int)isr13, 0x08, 0x8e);
	idt_set_gate(14,(unsigned int)isr14, 0x08, 0x8e);
	idt_set_gate(15,(unsigned int)isr15, 0x08, 0x8e);
	idt_set_gate(16,(unsigned int)isr16, 0x08, 0x8e);
	idt_set_gate(17,(unsigned int)isr17, 0x08, 0x8e);
	idt_set_gate(18,(unsigned int)isr18, 0x08, 0x8e);
	idt_set_gate(19,(unsigned int)isr19, 0x08, 0x8e);
	idt_set_gate(20,(unsigned int)isr20, 0x08, 0x8e);
	idt_set_gate(21,(unsigned int)isr21, 0x08, 0x8e);
	idt_set_gate(22,(unsigned int)isr22, 0x08, 0x8e);
	idt_set_gate(23,(unsigned int)isr23, 0x08, 0x8e);
	idt_set_gate(24,(unsigned int)isr24, 0x08, 0x8e);
	idt_set_gate(25,(unsigned int)isr25, 0x08, 0x8e);
	idt_set_gate(26,(unsigned int)isr26, 0x08, 0x8e);
	idt_set_gate(27,(unsigned int)isr27, 0x08, 0x8e);
	idt_set_gate(28,(unsigned int)isr28, 0x08, 0x8e);
	idt_set_gate(29,(unsigned int)isr29, 0x08, 0x8e);
	idt_set_gate(30,(unsigned int)isr30, 0x08, 0x8e);
	idt_set_gate(31,(unsigned int)isr31, 0x08, 0x8e);
	init_pic();
	write("after init pic");
	//and now for the irqs
	idt_set_gate(32,(unsigned int)irq32, 0x08, 0x8e);
	idt_set_gate(33,(unsigned int)irq33, 0x08, 0x8e);
	idt_set_gate(34,(unsigned int)irq34, 0x08, 0x8e);
	idt_set_gate(35,(unsigned int)irq35, 0x08, 0x8e);
	idt_set_gate(36,(unsigned int)irq36, 0x08, 0x8e);
	idt_set_gate(37,(unsigned int)irq37, 0x08, 0x8e);
	idt_set_gate(38,(unsigned int)irq38, 0x08, 0x8e);
	idt_set_gate(39,(unsigned int)irq39, 0x08, 0x8e);
	idt_set_gate(40,(unsigned int)irq40, 0x08, 0x8e);
	idt_set_gate(41,(unsigned int)irq41, 0x08, 0x8e);
	idt_set_gate(42,(unsigned int)irq42, 0x08, 0x8e);
	idt_set_gate(43,(unsigned int)irq43, 0x08, 0x8e);
	idt_set_gate(44,(unsigned int)irq44, 0x08, 0x8e);
	idt_set_gate(45,(unsigned int)irq45, 0x08, 0x8e);
	idt_set_gate(46,(unsigned int)irq46, 0x08, 0x8e);
	idt_set_gate(47,(unsigned int)irq47, 0x08, 0x8e);
	
	
	unsigned int i;
	for (i = 48; i < 255; i++)
	{
		idt_set_gate(i,(unsigned int) 0, 0x0, 0x0);
	}
	
	setIdt((unsigned int)&idt_ptr);
}
void idt_set_gate(unsigned char num, unsigned int base, unsigned short int sel, unsigned char flags)
{
   idt_entries[num].base_lo = base & 0xFFFF;
   idt_entries[num].base_hi = (base >> 16) & 0xFFFF;

   idt_entries[num].sel     = sel;
   idt_entries[num].always0 = 0;

   idt_entries[num].flags   = flags /* | 0x60 */;	
}

struct gdt_ptr gp;
struct gdt_entry gdt[5];
void init_gdt()
{
    
    gp.limit = (sizeof(struct gdt_entry) * 6) - 1;
    gp.base = (int) &gdt;

    
    gdt_set_gate(0, 0, 0, 0, 0);

    // kernel code segment
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x10 | 0X0a | 0x80 , 0x40 | 0x80);

    // kernel data segment
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x10 | 0X02 | 0x80 , 0x40 | 0x80);

        //user segments
        gdt_set_gate(3, 0, 0xFFFFFFFF, 0x10 | 0X0a | 0x80 , 0x40 | 0x80);
        gdt_set_gate(4, 0, 0xFFFFFFFF, 0x10 | 0X02 | 0x80 , 0x40 | 0x80);
        
        
    dt_flush();
    
}


void gdt_set_gate(int num, int base, int limit, char access, char gran) {
    /* Setup the descriptor base address */
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    /* Setup the descriptor limits */
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);

    /* Finally, set up the granularity and access flags */
    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}
