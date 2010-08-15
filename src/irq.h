typedef struct {
	unsigned int gs, fs, es, ds;	//pushed manually
	unsigned int edi, esi, ebp, int_esp, ebx, edx, ecx, eax; //esp from pushad; uninteresting
	unsigned int int_no, err_code;	//pushed by us
	unsigned int eip, cs, eflags, esp, ss; //pushed automatically by CPU
}__attribute__ ((packed)) regs;

regs *irq_handler(regs *r);
void init_pic(void);
void outb(short param1, char param2);
