section .data
gdt:
	dw 0
	dw 0
	dw 0
	dw 0
	dw 0xFFFF
	dw 0
	db 0
	db 0x9A
	db 0xCF
	db 0
	dw 0xFFFF
	dw 0
	db 0
	db 0x92
	db 0xCF
	db 0
gdt_end equ $ - gdt

gdtr:
	dw gdt_end - 1
	dd gdt

section .text
global install_gdt

install_gdt:
	cli
	lgdt [gdtr]

	mov eax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	jmp 0x08:.flush
.flush:
	ret
