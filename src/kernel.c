#include "console.h"
#include "desctbl.h"
void kmain( void* mbd, unsigned int magic )
{
   if ( magic != 0x2BADB002 )
   {
      write("the bootloader made a booboo :(");
   }
    char * boot_loader_name =(char*) ((long*)mbd)[16];
    write("testing write to screen");
    write("going to setup GDT hold on to your boots :|");
    init_descriptor_tables();
   write("phew that went well");
   write("let's try some interrupts :|");
   write("inter 3 and 4");
   asm volatile ("int $0x3");
   write("and nothing happens");
}


