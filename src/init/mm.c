#include "../include/console.h"
#include "../include/mm.h"

void init_mm(){
    write("kernel starts at:");
	writehex(&phys_kernel_start);
	write("kernel ends at:");
	writehex(&phys_kernel_end);
    unsigned int temp;
    temp = &phys_kernel_end;
    temp++;
    while( temp != ((temp/4096)*4096)){
        temp++; //aligning number to 4kb
    }
    unsigned int *page_directory = (unsigned int *) temp;
    unsigned int *page_table = (unsigned int *) temp+4096;
    //filling the table
    unsigned long addr = 0;
    unsigned int i;
    for(i=0;i<1024;i++){
        page_table[i] = addr | 3; //setting the correct flags for each table
        addr += 4096;
    }
    page_directory[0] = page_table;
    page_directory[0] = page_directory[0] | 3; //set the flags
    //set other page_directorys to not enabled 4 meg of ram should be enough for now
    for(i=1;i<1024;i++){
        page_directory[i] = 0 | 2;
    }
    write_cr3(page_directory);
    write_cr0(read_cr0 | 0x80000000);
}
void * kalloc(unsigned int size){

}
