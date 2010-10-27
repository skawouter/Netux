#include "../include/console.h"
#include "../include/mm.h"
//extern unsigned int endkernel;
extern unsigned int phys_kernel_start;
extern unsigned int phys_kernel_end;
void init_mm(){
	writenumber(phys_kernel_start);
	if (phys_kernel_end){
       		writenumber(phys_kernel_end);
    	}
	else{
		write("error meuh");
	}
}

