#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>
#include "stdio.h"
 
/* Check if the compiler thinks if we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif

extern void install_gdt();

typedef struct GDT {
	uint16_t limit;
	uint32_t base;
	uint8_t  type;
} GDT;

/*
 * target: pointer to the 8-byte GDT entry
 * source: structure representing the GDT entry
*/
void encodeGdtEntry(uint8_t *target, uint16_t limit, uint32_t base, uint8_t type) 
{
	// check to see if limit can be encoded
	if ((limit > 65536) && (limit & 0xFFF) != 0xFFF) {
		print("GDT limit can't be encoded");
	}

	if (limit > 65536) {
		limit = limit >> 12;
		target[6] = 0xC0;
	} else {
		target[6] = 0x40;
	}

	target[0] = limit & 0xFF;
	target[1] = (limit >> 8) & 0xFF;
	target[6] |= (limit >> 16) & 0xFF;

	target[2] = base & 0xFF;
	target[3] = (base >> 8) & 0xFF;
	target[4] = (base >> 16) & 0xFF;
	target[7] = (base >> 24) & 0xFF;

	target[5] = type;
}

GDT gdt_entries[3];

void kernel_main()
{
	terminal_initialize();
	print("Hello, kernel World!\n");
	print("Initializing GDT...");
	encodeGdtEntry(&gdt_entries[0], 0, 0, 0); // Null entry or bad things happen
	encodeGdtEntry(&gdt_entries[1], 0xFFFF, 0, 0x9A);
	encodeGdtEntry(&gdt_entries[2], 0xFFFF, 0, 0x92);
	install_gdt(gdt_entries, sizeof(gdt_entries));
	print(" Done!\n");
}
