#include "./include/console.h"
#include "./include/desctbl.h"

void kmain( void* mbd, unsigned int magic )
{
   if ( magic != 0x2BADB002 )
   {
      write("the bootloader made a booboo :(");
   }
    char * boot_loader_name =(char*) ((long*)mbd)[16];
    write("testing write to screen");
    write("going to setup GDT hold on to your boots :|");
    init_descriptor_tables(); // hah it also inits the isr and hw irq thingys!
    asm volatile("sti");
	startconsole();
  // write("and nothing happens");
   while(1)
    { asm volatile("NOP");}
}
