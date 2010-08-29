//keyboard handler
#include "../include/console.h"
char keyb_handle(short inp){
	if (inp-16 < 43) {
		static const char keybmap[44]={'q','w','e','r','t','y','u','i','o','p',0,0,1,0,'a','s','d','f','g','h','j','k','l',0,0,0,0,0,'z','x','c','v','b','n','m',0,0,0,0,0,0,' '};
		char key[2];
		key[1] = 0;
		key[0] = keybmap[inp-16];
		handleinput(key);	
	}
	if (inp-16 > 43 && inp-16 < 100) {
		writenumber(inp);
	}
	return 1;
}
