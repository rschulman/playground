#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>
#include "stdio.h"

struct IDTDescriber {
	uint16_t offset_low;		// bits 0 - 15
	uint16_t selector;		// Code segment in either GDT or LDT (GDT for now)
	uint8_t  zero;			// Just because we need some zeroes
	uint8_t  type_attr;		// Type bits
	uint16_t offset_high;	// bits 16 - 31
} __attribute__((packed));

struct IDTptr {
	uint16_t idt_limit;
	uint32_t idt_base;
} __attribute__((packed));

struct IDTDescriber idts[256]; // Allocate a chunk of memory for our idts
struct IDTptr idtp;
extern void load_idt();
extern void isr_wrapper();

void write_idt (struct IDTDescriber * idt, uint32_t offset, uint16_t selector, bool active) {
	idt->offset_low = offset & 0xFFFF;
	idt->offset_high = (offset >> 16) & 0xFFFF;
	idt->selector = selector;
	idt->zero = 0;
	if (active) {
		idt->type_attr = 0x8E;
	} else {
		idt->type_attr = 0x0E; // Set present flag to false if not active.
	}

	return;
}

void fault() {
	print("OMG A FAULT!\n");
}

void install_idts () {
	for ( uint16_t counter = 0; counter < 256; counter++ ) {
		if ( counter == 15 || counter == 31 || (counter > 19 && counter < 30) ) {
			write_idt(&idts[counter], &isr_wrapper, 0x80, false);
		} else {
			write_idt(&idts[counter], &isr_wrapper, 0x80, true);
		}
	}
	print("\nDebugs:\n");
	fprint("Address of fault: %h\n", &isr_wrapper);
	fprint("Offset low: %h\n", idts[0].offset_low);
	fprint("Offset high: %h\n", idts[0].offset_high);
	idtp.idt_limit = (sizeof (struct IDTDescriber) * 256) - 1;
	idtp.idt_base = &idts;
	load_idt();
}