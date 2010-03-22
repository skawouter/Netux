
extern void gdt_flush(unsigned long int);

void init_gdt();
void gdt_set_gate(long int,unsigned long int,unsigned long int,unsigned short int,unsigned short int);

struct gdt_entry
{
	unsigned int limit_low ;
	unsigned int base_low ;
	unsigned short int base_middle ;
	unsigned short int access ;
	unsigned short int granularity ;
	unsigned short int base_high ;
} __attribute__ ((packed));
typedef struct gdt_entry gdt_entry_t;
/* pointer for the gdt entry*/

struct gdt_ptr
{
	unsigned int limit ;
	unsigned long int base ;
} __attribute__ ((packed));
typedef struct gdt_ptr gdt_ptr_t;
void init_descriptor_tables();