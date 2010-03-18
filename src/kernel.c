unsigned int position;
void realwrite(unsigned int pos,unsigned int val)
{
	char *vidmem = (char *) 0xB8000;
	vidmem[pos]=val+0x30;

}
void testwrite(char *writethis,unsigned int buff)
{
	char *vidmem = (char *) 0xB8000;
	unsigned int i = position;
	for (i=i;i < (buff*2)+position; i+=2)
	{
		vidmem[i]=writethis[i/2];
		vidmem[i+1]=0x07;
		realwrite(20*(i+1),i);
	}
	position += (buff*2);
}

void clearscreen()
{
	char *vidmem = (char *) 0xB8000;
	unsigned int i=0;
	while(i<(80*50*2))
	{
		vidmem[i] = ' ';
		i++;
		vidmem[i] = 0x07;
		i++;
		position=0;
	}
}
void kmain( void* mbd, unsigned int magic )
{
   if ( magic != 0x2BADB002 )
   {
      testwrite("Bootloader did not play nice",30);
   }
    char * boot_loader_name =(char*) ((long*)mbd)[16];
    clearscreen();
//    realwrite(150);
    testwrite("ab",2);
//    realwrite(170);
    testwrite("cd",2);
//    realwrite(180);
}


