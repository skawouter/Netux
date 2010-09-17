#include "../include/console.h"
#include "../include/math.h"

unsigned int consmem[2][80*25*2];
unsigned int position[2];
unsigned int lastconsole = 0;
char input[40];
char inputenabled = 0;
unsigned int currchar = 0;
void writenumber(unsigned int inp)
{
	int trillion = inp/1000000000;
	inp = inp - (trillion * 1000000000);
	int hundmillion = inp/100000000;
	inp = inp - (hundmillion * 100000000);
	int tenmillion = inp/10000000;
	inp = inp - (tenmillion * 10000000);
	int million = inp/1000000;
	inp = inp - (million * 1000000);
	int hundredthousand = inp/100000;
	inp = inp - (hundredthousand * 100000);
	int tenthousand = inp/10000;
	inp = inp - (tenthousand * 10000);
	int thousand = inp/1000;
	inp = inp - (thousand * 1000);
	int hunderd = inp/100;
	inp = inp - (hunderd * 100);
	int ten = inp/10;
	inp = inp - (10*ten);
	int zero = inp;
	char getal[11];
	getal[0] = trillion +48;
	getal[1] = hundmillion +48;
	getal[2] = tenmillion+48;
	getal[3] = million + 48;
	getal[4] = hundredthousand +48;
	getal[5] = tenthousand +48;
	getal[6] = thousand +48;
	getal[7] = hunderd + 48;
	getal[8] = ten + 48;
	getal[9] = zero + 48;
	getal[10] = 0;
	write(getal);
}
void writehex(unsigned int inp){
        short x;
        unsigned int temp;
        char output[8];
        for (x=6;x>-1;x--){
                temp = inp / doexpon(16,x);
                inp -= temp * doexpon(16,x);
                output[6-x] = convertnumtochar(temp);
        }
        output[7] = convertnumtochar(inp);
        output[8] = 0;
        write(output);
}
char convertnumtochar(unsigned int inp)
{
	if (inp > 15)
		return 0;
	switch(inp){
		case 10:
			return 'A';
			break;
		case 11:
			return 'B';
			break;			
		case 12:
			return 'C';
			break;			
		case 13:
			return 'D';
			break;			
		case 14:
			return 'E';
			break;			
		case 15:
			return 'F';
			break;			
		default:
			return inp+48;
			break;			
	}
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
	if (inputenabled==1){
		position[lastconsole] = position[lastconsole] / 160;
		position[lastconsole]  = (position[lastconsole]+1) * 160;		
	}
	writetoconsole(writethis,lastconsole);
	position[lastconsole] = position[lastconsole] / 160;
	position[lastconsole]  = (position[lastconsole]+1) * 160;
	if (inputenabled==1){
		writetoconsole("$>",lastconsole);
	}
}
void startconsole(void)
{
	//clearconsole(0);
	write("it starts now :)");
	writetoconsole("$>",0);
	inputenabled=1;
}
void handleinput(char *chr)
{
	if (inputenabled==1)
	{
		
		if (*chr != ENTERCHAR)
		{
			writetoconsole(chr,0);
			input[currchar] =  (char)*chr;
		}
		currchar += 1;
		if (*chr == ENTERCHAR || currchar == 40)
		{
			currchar = 0;
			executecommand();
			int x ;
			for (x = 0;x < 40; x++){
				input[x] = 0;
			}
		}
	}
}
void executecommand(void){
	write(input);
}
