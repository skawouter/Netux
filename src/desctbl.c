#include "desctbl.h"
#include "console.h"

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

	unsigned int i;
	for (i = 32; i < 255; i++)
	{
		idt_set_gate(i,(unsigned int) 0, 0x0, 0x0);
	}
	setIdt((unsigned int)&idt_ptr);
	asm volatile("sti");
}
void idt_set_gate(unsigned char num, unsigned int base, unsigned short int sel, unsigned char flags)
{
   idt_entries[num].base_lo = base & 0xFFFF;
   idt_entries[num].base_hi = (base >> 16) & 0xFFFF;

   idt_entries[num].sel     = sel;
   idt_entries[num].always0 = 0;

   idt_entries[num].flags   = flags /* | 0x60 */;	
}

void init_gdt()
{
	unsigned char target[8*3]; 
	//start with zero table
	target[0]  = (0 & 0xff);
	target[1] = (0 >>8) & 0xFF;
	target[2] = 0 & 0Xff;
	target[3] = (0 >> 8) & 0xFF;
	target[4] = (0 >> 16) & 0xFF;
	target[5] = 0;
	target[6] = (0 >> 16) & 0xFF;
	target[7] = (0 >> 24) & 0XFF;
	//then the code table
	target[8]  = (0xFFFFFFFF & 0xff);
	target[9] = (0xFFFFFFFF >>8) & 0xFF;
	target[10] = 0 & 0Xff;
	target[11] = (0 >> 8) & 0xFF;
	target[12] = (0 >> 16) & 0xFF;	
	target[13] = 0x9A;
	target[14] = (0xFFFFFFFF >> 16) & 0xFF;
	target[15] = (0 >> 24) & 0XFF;
	//then the data table
	target[16]  = (0xFFFFFFFF & 0xff);
	target[17] = (0xFFFFFFFF >>8) & 0xFF;
	target[18] = 0 & 0Xff;
	target[19] = (0 >> 8) & 0xFF;
	target[20] = (0 >> 16) & 0xFF;	
	target[21] = 0x92;
	target[22] = (0xFFFFFFFF >> 16) & 0xFF;
	target[23] = (0 >> 24) & 0XFF;	
	write("writing our GDT table");
	int i = 0;
	for (i=0;i<24;i++)
	{
		writenumber((unsigned int)target[i]);
	}
	setGdt(target,sizeof(target));
}
