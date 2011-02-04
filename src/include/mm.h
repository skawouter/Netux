extern unsigned int phys_kernel_start;
extern unsigned int phys_kernel_end;
extern unsigned int read_cr0;
extern unsigned int read_cr3;
extern void write_cr0(unsigned int v);
extern void write_cr3(unsigned int v);

void init_mm();
void * kalloc(unsigned int size);
