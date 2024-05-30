#![no_std]
#![no_main]
use bootloader::{entry_point, BootInfo};
use core::panic::PanicInfo;
use netux::memory::{active_level_4_table, translate_addr};
use netux::{print, println};
use x86_64::{structures::paging::PageTable, VirtAddr};

#[panic_handler]
fn panic(info: &PanicInfo) -> ! {
    println!("{}", info);
    loop {}
}
entry_point!(kernel_main);

fn kernel_main(boot_info: &'static BootInfo) -> ! {
    println!("Startup");
    netux::init();
    println!("Mem offset {:#X}", boot_info.physical_memory_offset);

    let phys_mem_offset = VirtAddr::new(boot_info.physical_memory_offset);
    
    let addresses = [
                // the identity-mapped vga buffer page
        0xb8000,
        // some code page
        0x201008,
        // some stack page
        0x0100_0020_1a10,
        // virtual address mapped to physical address 0
        boot_info.physical_memory_offset,
    ];
    for &addr in &addresses {
        let virt = VirtAddr::new(addr);
        let phys = unsafe {
            translate_addr(virt, phys_mem_offset)
        };
        println!("{:?} -> {:?}", virt, phys)
    }
    println!("Done let's loop");
    netux::hlt_loop();
}
