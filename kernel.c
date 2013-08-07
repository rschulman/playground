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

void kernel_main()
{
	terminal_initialize();
	print("Hello, kernel World!\n");
	print("Initializing GDT...");
	install_gdt();
	print(" Done!\n");
}
