
//declaration of all our interrupts (now til 31 wich are the processor interrupts)
extern void dt_flush();
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

extern void irq32();
extern void irq33();
extern void irq34();
extern void irq35();
extern void irq36();
extern void irq37();
extern void irq38();
extern void irq39();
extern void irq40();
extern void irq41();
extern void irq42();
extern void irq43();
extern void irq44();
extern void irq45();
extern void irq46();
extern void irq47();

extern void setGdt(unsigned char[24],int);
extern void setIdt(unsigned int);
void idt_set_gate(unsigned char, unsigned int, unsigned short int, unsigned char);

void init_gdt();
void init_descriptor_tables();
void init_idt();


struct idt_entry_struct
{
	unsigned short int base_lo;
	unsigned short int sel;
	unsigned char always0;
	unsigned char flags;
	unsigned short int base_hi;
}  __attribute__((packed));

typedef struct idt_entry_struct idt_entry_t;

struct idt_ptr_struct
{
	unsigned short int limit;
	unsigned int base;
}  __attribute__((packed));
typedef struct idt_ptr_struct idt_ptr_t;

struct gdt_entry {
    short limit_low;
    short base_low;
    char base_middle;
    char access;
    char granularity;
    char base_high;
} __attribute__((packed));

struct gdt_ptr {
    short limit;
    int base;
} __attribute__((packed));
void gdt_set_gate(int num, int base, int limit, char access, char gran);
