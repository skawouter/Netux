#include "console.h"
unsigned int consmem[2][80*25*2];
unsigned int position[2];
unsigned int lastconsole = 0;

void writenumber(unsigned int inp)
{
	int hunderd = inp/100;
	inp = inp - (hunderd * 100);
	int ten = inp/10;
	inp = inp - (10*ten);
	int zero = inp;
	char getal[4];
	getal[0] = hunderd + 48;
	getal[1] = ten + 48;
	getal[2] = zero + 48;
	getal[3] = 0;
	write(getal);
}
void writetoconsole(char *writethis, unsigned int console)
{
	if ( position[console] == 0 ){
		clearconsole(console);
	}
	unsigned int i = 0;
	while ( writethis[i] != 0 ){	
		if ( position[console]+2 >= 80*25*2 ) 
		{
			scrollconsole(console);
		}
		consmem[console][position[console]] = writethis[i];
		i++;
		position[console] += 2;
	}
	
	refreshconsole(console);
}
void scrollconsole(unsigned int console){
	unsigned int i;
	for (i=0; i <= (80*25*2)-160;i++)
	{
		consmem[console][i] = consmem[console][i+160];
	}
	for(i=(80*25*2)-160; i <= (80*25*2);i+=2){
		consmem[console][i] = ' ';
	}
	position[console] -= 160;
}
void setconsole(unsigned int console){
	lastconsole = console;
	refreshconsole(console);
}
void refreshconsole(unsigned int console){
	char *vidmem = (char *) 0xB8000;
	unsigned int i = 0;
	for (i = 0; i < 80*25*2; i++) {
		vidmem[i] = consmem[console][i];	
	}
}
void clearconsole(unsigned int console){
	unsigned int i = 0;
	for (i = 0; i < 80*25*2; i++) {
		consmem[console][i]  = ' ';
		consmem[console][i+1] = 0x07;
		i++;
	}
	position[console]=0;
	refreshconsole(console);
}
void write(char *writethis)
{
	writetoconsole(writethis,lastconsole);
	position[lastconsole] = position[lastconsole] / 160;
	position[lastconsole]  = (position[lastconsole]+1) * 160;

}