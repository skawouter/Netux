[GLOBAL setGdt]
[GLOBAL setIdt]

gdtr DW 0
	DD 0

setGdt:
	   MOV   EAX, [esp + 4]
	   MOV   [gdtr + 2], EAX
	   MOV   AX, [ESP + 8]
	   MOV   [gdtr], AX
	   LGDT  [gdtr]
	   jmp 0x08:reload_CS 		;our code is at 0x08 now so we jump there
	   RET

reload_CS:
	mov ax, 0x10				; and our data is at 0x10 so we load that into the segment registers
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	ret
	
setIdt:
	mov eax, [esp+4]
	lidt [eax]
	ret
	