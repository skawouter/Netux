#include "inter.h"
#include "console.h"
gdt_entry_t gdt_entries[5]; 			//yes 5!
gdt_ptr_t	gdt_entry_ptr;
//idt_entry   idt_entries[256];			//declaretion for interrupt table
//idt_ptr    idt_entry_ptr;

//initializing :)
//can be called from asm
void init_descriptor_tables()
{
	write("onto the init");
	init_gdt();
	return;
}

void init_gdt()
{
	gdt_entry_ptr.limit = (sizeof(gdt_entry_t)  * 5) -1; 		//limit should be all the entries minus 1
	gdt_entry_ptr.base = (unsigned long int)&gdt_entries;			//adres of the beginning of the entries
	write("did the entry pointer");
	//now we're going to fill our segment descriptors
	gdt_set_gate(0,0,0,0,0);							//the processor likes a null entry very much
	gdt_set_gate(1,0,0xFFFFFFFF, 0x9A, 0xCF);			//all segments encompass the entire 4GB of ram 
												//this one is a code segment at kernel level
	gdt_set_gate(2,0,0xFFFFFFFF, 0x92, 0xCF);			//this one is a data segment at kernel level
	gdt_set_gate(3,0,0xFFFFFFFF, 0xFA, 0xCF);			//this one is a code segment at user level
	gdt_set_gate(4,0,0xFFFFFFFF, 0xF2, 0xCF);			//this one is a data segment at user level
	write("we set all the crap") ;						// all of them are with a block size of 1kb 
	gdt_flush((unsigned long int)&gdt_entry_ptr); 	//yeah i forgot this so i thought it worked
}
void gdt_set_gate(long int num, unsigned long int base, unsigned long int limit, unsigned short int access, unsigned short int  gran)
{
	gdt_entries[num].base_low 	= (base & 0xFFFF);			// why & 0xFFFF i don't get it :s
	gdt_entries[num].base_middle = (base >> 16) & 0xff;
	gdt_entries[num].base_high	= (base >> 24) & 0xff;
	
	gdt_entries[num].limit_low 	= (limit & 0xFFFF);
	gdt_entries[num].granularity    = (limit >> 16) & 0x0F;
	
	gdt_entries[num].granularity	|= gran & 0x0F;
	gdt_entries[num].access		= access;
}