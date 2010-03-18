void testwrite(char *writethis,unsigned int buff)
{
	char *vidmem = (char *) 0xB8000;
	unsigned int i=0;
	for (i=0;i < buff*2; i+=2)
	{
		vidmem[i]=writethis[i/2];
	}
}

void kmain( void* mbd, unsigned int magic )
{
   if ( magic != 0x2BADB002 )
   {
      testwrite("Bootloader did not play nice",30);
   }
    char * boot_loader_name =(char*) ((long*)mbd)[16];
    testwrite("testerder",9);
}


