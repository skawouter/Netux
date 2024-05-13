#![no_std]
#![no_main]
use bootloader::{entry_point, BootInfo};
use netux::println;
use core::{panic::PanicInfo};

#[panic_handler]
fn panic(info: &PanicInfo) -> ! {
    println!("{}", info);
    loop {}
}
entry_point!(kernel_main);

fn kernel_main(boot_info: &'static BootInfo) -> ! {
    println!("Startup");
    netux::init();
    //trigger a page fault
    /*unsafe {
        *(0xdeadbeef as *mut u8) = 42;
    }*/

    //trigger breakpoint
    /*unsafe {
        asm!("int3", options(nomem, nostack));
    }*/

    /*fn stack_overflow() {
        stack_overflow();
    }
    stack_overflow();*/
    println!("Done let's loop");
    netux::hlt_loop();
}
