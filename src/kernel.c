#include "./include/console.h"
#include "./include/desctbl.h"
#include "./include/device.h"

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
    write("write hexes");
	writehex(10);
    writehex(31);
    writehex(40);
    init_devices();
    startconsole();
    asm volatile("sti");
	
  // write("and nothing happens");
   while(1)
    { asm volatile("NOP");}
}
/* MOVE THIS TO MATH.C */
