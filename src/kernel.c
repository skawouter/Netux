#include "./include/console.h"
#include "./include/desctbl.h"
#include "./include/device.h"
#include "./include/irq.h"
#include "./include/keyb.h"
#include "./include/mm.h"

int timertest(){
	write("timer received");
	return 0;
}

void kmain( void* mbd, unsigned int magic )
{
   if ( magic != 0x2BADB002 )
   {
      write("the bootloader made a booboo :(");
   }
    char * boot_loader_name =(char*) ((long*)mbd)[16];
    write(boot_loader_name);
    write("testing write to screen");
    write("going to setup GDT hold on to your boots :|");
    init_descriptor_tables(); // hah it also inits the isr and hw irq thingys!
    write("register keyboard handle and time handle");
    register_irq(0x21,&keyb_handle);
    register_irq(0x20,&timertest);
    write("init devices");
    init_devices();
    write("init memory");
    init_mm();
    write("start console");
    startconsole();
    asm volatile("sti");
    write("just enabled irqs and unregister timer :)");
  // write("and nothing happens");
    unregister_irq(0x20);
   while(1)
    { asm volatile("HLT");}
}
/* MOVE THIS TO MATH.C */
