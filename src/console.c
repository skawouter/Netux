#include "console.h"
unsigned int consmem[2][80*25*2];
unsigned int position[2];
unsigned int lastconsole = 0;
void writetoconsole(char *writethis, unsigned int console)
{
	if ( position[console] == 0 ){
		clearconsole(console);
	}
	unsigned int i = 0;
	while ( writethis[i] != 0 ){	
		consmem[console][position[console]] = writethis[i];
		i++;
		position[console] += 2;
	}
	refreshconsole(console);
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
	position[lastconsole] += 160;

}