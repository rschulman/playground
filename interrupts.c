#include "stdio.h"
#include "interrupts.h"

idt_entry_t idt_entries[256];
idt_pointer_t idt_location;

static void init_idt()
{
	idt_location.limit = sizeof(idt_entry_t) * 256 - 1;
	idt_location.base = (uint32_t)&idt_entries;

	memset(&idt_entries, 0, sizeof(idt_entry_t) * 256);

	idt_set_gate( 0, (uint32_t)isr0 , 0x08, 0x8E);
	idt_set_gate( 0, (uint32_t)isr1 , 0x08, 0x8E);
	idt_set_gate( 0, (uint32_t)isr2 , 0x08, 0x8E);
	idt_set_gate( 0, (uint32_t)isr3 , 0x08, 0x8E);
	idt_set_gate( 0, (uint32_t)isr4 , 0x08, 0x8E);
	idt_set_gate( 0, (uint32_t)isr5 , 0x08, 0x8E);
	idt_set_gate( 0, (uint32_t)isr6 , 0x08, 0x8E);
	idt_set_gate( 0, (uint32_t)isr7 , 0x08, 0x8E);
	idt_set_gate( 0, (uint32_t)isr8 , 0x08, 0x8E);
	idt_set_gate( 0, (uint32_t)isr9 , 0x08, 0x8E);
	idt_set_gate( 0, (uint32_t)isr10 , 0x08, 0x8E);
	idt_set_gate( 0, (uint32_t)isr11 , 0x08, 0x8E);
	idt_set_gate( 0, (uint32_t)isr12 , 0x08, 0x8E);
	idt_set_gate( 0, (uint32_t)isr13 , 0x08, 0x8E);
	idt_set_gate( 0, (uint32_t)isr14 , 0x08, 0x8E);
	idt_set_gate( 0, (uint32_t)isr15 , 0x08, 0x8E);
	idt_set_gate( 0, (uint32_t)isr16 , 0x08, 0x8E);
	idt_set_gate( 0, (uint32_t)isr17 , 0x08, 0x8E);
	idt_set_gate( 0, (uint32_t)isr18 , 0x08, 0x8E);
	idt_set_gate( 0, (uint32_t)isr19 , 0x08, 0x8E);
	idt_set_gate( 0, (uint32_t)isr20 , 0x08, 0x8E);
	idt_set_gate( 0, (uint32_t)isr21 , 0x08, 0x8E);
	idt_set_gate( 0, (uint32_t)isr22 , 0x08, 0x8E);
	idt_set_gate( 0, (uint32_t)isr23 , 0x08, 0x8E);
	idt_set_gate( 0, (uint32_t)isr24 , 0x08, 0x8E);
	idt_set_gate( 0, (uint32_t)isr25 , 0x08, 0x8E);
	idt_set_gate( 0, (uint32_t)isr26 , 0x08, 0x8E);
	idt_set_gate( 0, (uint32_t)isr27 , 0x08, 0x8E);
	idt_set_gate( 0, (uint32_t)isr28 , 0x08, 0x8E);
	idt_set_gate( 0, (uint32_t)isr29 , 0x08, 0x8E);
	idt_set_gate( 0, (uint32_t)isr30 , 0x08, 0x8E);
	idt_set_gate( 0, (uint32_t)isr31 , 0x08, 0x8E);

	idt_flush((uint32_t)&idt_location;
}

static void idt_set_gate(uint8_t num, uint32_t base, uint16_t selector, uint8_t flags)
{
	idt_entries[num].lower_base = base & 0xFFFF;
	idt_entries[num].upper_base = (base >> 16) & 0xFFFF;

	idt_entires[num].selector = selector;
	idt_entries[num].flags = flags;
	idt_entries[num].zero = 0;
}

void interrupt_handler(registers_t registers)
{
	fprint("Interrupt received: %d\n", registers.int_no);
}
