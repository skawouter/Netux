#define ENTERCHAR 1
#define BACKSPACECHAR 8
void writetoconsole(char *writethis, unsigned int console);
void refreshconsole(unsigned int console);
void clearconsole(unsigned int console);
void setconsole(unsigned int console);
void write(char *writethis);
void scrollconsole(unsigned int console);
void writenumber(unsigned int inp);
void executecommand(void);
void startconsole(void);
void handleinput(char *chr);
void writehex(unsigned int inp);
char convertnumtochar(unsigned int inp);
