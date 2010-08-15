[GLOBAL dt_flush]
[GLOBAL setIdt]
[extern gp]
gdtr DW 0
	DD 0

dt_flush:
        lgdt [gp]
        mov ax,0x10
        mov ds,ax
        mov es,ax
        mov fs,ax
        mov gs,ax
        mov ss,ax
        jmp 0x08:flush2
flush2:
        ret

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
	
