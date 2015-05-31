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
	unsigned char result;
	__asm__ volatile ("inb %1, %0" : "=a" (result) : "Nd" (_port));
	return result;
}

static inline void __attribute__((always_inline)) outl(short _port, unsigned long _data) {
	__asm__ volatile ("outl %0, %1" : : "a" (_data), "Nd" (_port));
}
static inline short __attribute__((always_inline)) inl(short _port) {
	unsigned long result;
	__asm__ volatile ("inl %1, %0" : "=a" (result) : "Nd" (_port));
	return result;
}
inline static unsigned short ins(unsigned short _port) {
	unsigned short rv;
	__asm__ volatile ("inw %1, %0" : "=a" (rv) : "dN" (_port));
	return rv;
}

struct irq_struct{
	char irq;
	int (*functpoint)();
};

struct irq_struct irqlist[255];
int register_irq(unsigned char irq, int (*functpoint)());
void unregister_irq(unsigned char irq); 
