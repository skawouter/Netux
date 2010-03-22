[GLOBAL gdt_flush]			; the function exposed 8)

gdt_flush:
	mov eax, [esp+4]		; put our parameter in eax
	lgdt [eax]				; this is our GDT load it and please don't crash
	

	jmp 0x08:.flush			; And now let's get back to the code
.flush:
	mov ax, 0x10			; 0x10 is our data segment let's put it in all of the segment registers
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	ret