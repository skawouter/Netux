global loader                 ; making entry point visible to linker
extern kmain

MEMALIGN equ 1<<0
MEMINFO equ 1<<1
FLAGS equ MEMALIGN | MEMINFO
MAGIC equ 0x1BADB002       ; 'magic number' lets bootloader find the header
CHECKSUM equ -(MAGIC + FLAGS) ; checksum required

section .text
align 4
MultiBootHeader:
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

; reserve initial kernel stack space
STACKSIZE equ  0x4000          ; that is, 16k.
loader:
   mov   esp, stack + STACKSIZE
   push  eax ; Multiboot magic number
   push  ebx                       ; Multiboot data structure
   call  kmain            ; call kernel proper

   cli
hang:
   hlt                    ; halt machine should kernel return
   jmp   hang

section .bss
align 4
stack:
    resb STACKSIZE
