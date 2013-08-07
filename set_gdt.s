.section .data
gdt:
	.word 0  		# First GDT entry is completely 0.
	.word 0
	.word 0
	.word 0
	.word 0xFFFF		# Second GDT entry for entire 4GiB of code.
	.word 0
	.byte 0
	.byte 0x9A
	.byte 0xCF
	.byte 0
	.word 0xFFFF		# Third GDT entry for entire 4GiB of data.
	.word 0
	.byte 0
	.byte 0x92
	.byte 0xCF
	.byte 0
gdt_end:
	.set gdt_size, gdt_end - gdt

gdtr:
	.word gdt_size
	.int gdt

.section .text
.global install_gdt

install_gdt:
	cli
	lgdt (gdtr)

	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss
	ljmp $0x08, $flush
flush:
	ret
