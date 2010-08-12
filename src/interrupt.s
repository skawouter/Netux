[EXTERN isr_handler]
[EXTERN irq_handler]

%macro ISR_NOERRORCODE 1
	[GLOBAL isr%1]
	isr%1:
		cli
		push byte 0
		push byte %1
		jmp isr_common
%endmacro

%macro IRQ 1
	[GLOBAL irq%1]
	irq%1:
		cli
		push byte 0
		push byte %1
		jmp irq_common
%endmacro%

%macro ISR_ERRORCODE 1
	[GLOBAL isr%1]
	isr%1:
		cli
		push byte %1
		jmp isr_common
%endmacro
;handling of errorcodes
IRQ 32
IRQ 33
IRQ 34
IRQ 35
IRQ 36
IRQ 37
IRQ 38
IRQ 39
IRQ 40
IRQ 41
IRQ 42
IRQ 43
IRQ 44
IRQ 45
IRQ 46

ISR_NOERRORCODE 0
ISR_NOERRORCODE 1
ISR_NOERRORCODE 2
ISR_NOERRORCODE 3
ISR_NOERRORCODE 4
ISR_NOERRORCODE 5
ISR_NOERRORCODE 6
ISR_NOERRORCODE 7
ISR_ERRORCODE 8
ISR_NOERRORCODE 9
ISR_ERRORCODE 10
ISR_ERRORCODE 11
ISR_ERRORCODE 12
ISR_ERRORCODE 13
ISR_ERRORCODE 14
ISR_NOERRORCODE 15
ISR_NOERRORCODE 16
ISR_NOERRORCODE 17
ISR_NOERRORCODE 18
ISR_NOERRORCODE 19
ISR_NOERRORCODE 20
ISR_NOERRORCODE 21
ISR_NOERRORCODE 22
ISR_NOERRORCODE 23
ISR_NOERRORCODE 24
ISR_NOERRORCODE 25
ISR_NOERRORCODE 26
ISR_NOERRORCODE 27
ISR_NOERRORCODE 28
ISR_NOERRORCODE 29
ISR_NOERRORCODE 30
ISR_NOERRORCODE 31	; this does everything from 32-255 for now
isr_common:
;save everything execute code for interrupt and return where we were aaaah...
	pushad	
	call isr_handler
	hlt 				; it's an error we're not going to return
irq_common:
	pushad
    push ds
    push es
    push fs
    push gs

	cld			;reset direction flag to known state
	;load kernel segments
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
	push esp
    call irq_handler
    mov esp, eax

	
	; pop from new stack
    pop gs
    pop fs
    pop es
    pop ds
    popad
    
    add esp, 8		;delete error code and interrupt number
    sti
    iret
