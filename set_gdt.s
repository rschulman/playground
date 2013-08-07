.section .data
gdt:
	.word 0  		# First GDT entry is completely 0.
	.word 0
	.word 0
	.word 0
	.word 0xFF		# Second GDT entry for entire 4GiB of code.
	.word 0
	.byte 0
	.byte 0x9A
	.word 0xFF		# Third GDT entry for entire 4GiB of data.
	.word 0
	.byte 0
	.byte 0x9A
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
	ret
