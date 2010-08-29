typedef struct {
	unsigned int gs, fs, es, ds;	//pushed manually
	unsigned int edi, esi, ebp, int_esp, ebx, edx, ecx, eax; //esp from pushad; uninteresting
	unsigned int int_no, err_code;	//pushed by us
	unsigned int eip, cs, eflags, esp, ss; //pushed automatically by CPU
}__attribute__ ((packed)) regs;

regs *irq_handler(regs *r);
void init_pic(void);
static inline void __attribute__((always_inline)) outb(short _port, char _data) {
	__asm__ volatile ("outb %0, %1" : : "a" (_data), "Nd" (_port));
}
static inline short __attribute__((always_inline)) inb(short _port) {
	short result;
	__asm__ volatile ("inb %1, %0" : "=a" (result) : "Nd" (_port));
	return result;
}