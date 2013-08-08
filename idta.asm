; Loads our IDT strucutre (from the idt.c file) into the processor

global load_idt
extern idtp

load_idt:
	lidt [idtp]
	ret
