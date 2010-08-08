[EXTERN isr_handler]
%macro ISR_NOERRORCODE 1
	[GLOBAL isr%1]
	isr%1:
		cli
		push byte 0
		push byte %1
		jmp isr_common
%endmacro
%macro ISR_ERRORCODE 1
	[GLOBAL isr%1]
	isr%1:
		cli
		push byte %1
		jmp isr_common
%endmacro
;handling of errorcodes
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
ISR_NOERRORCODE 31
ISR_NOERRORCODE 32		; this does everything from 32-255 for now
isr_common:
	
;save everything execute code for interrupt and return where we were aaaah...
	pushad
	;mov ax, ds ;save ds
	;push eax	 ;put it on the stack

	;mov ax, 0x10 ; load the ds descriptor
	;mov ds, ax
	;mov es, ax
	;hlt
	;mov fs, ax
	
	;mov gs, ax
	
	
	call isr_handler
	hlt
	;pop eax		;get our saved state back
	;mov ds, ax
	;mov es, ax
	;mov fs, ax

	;mov gs, ax
	
	popad			;get all our registers back
	;add esp, 8		;our parameters get cleaned up
	;sti			; ready for more
	;O32 
	iret		;get back to our running code
	
