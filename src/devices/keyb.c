//keyboard handler
#include "../include/console.h"
#include "../include/irq.h"
int keyb_handle(){
	short inp = inb(0x60);
	char keys[2];
	switch( inp )
	{
		case 0x0e : 	
				keys[0] = 8;
				keys[1] = 0;	
				handleinput(keys);
		
	}
	if (inp-16 < 43) {
		static const char keybmap[44]={'q','w','e','r','t','y','u','i','o','p',0,0,1,0,'a','s','d','f','g','h','j','k','l',0,0,0,0,0,'z','x','c','v','b','n','m',0,0,0,0,0,0,' '};
		keys[1] = 0;
		keys[0] = keybmap[inp-16];
		handleinput(keys);	
	}
	if (inp-16 > 43 && inp-16 < 100) {
		writenumber(inp);
	}
	return 1;
}
