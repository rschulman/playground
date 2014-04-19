#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>
#include "descriptors.h"

gdt_entry_t     gdt_entries[5];
GDT_t           gdt_ptr;

extern void install_gdt();

void write_descriptor_gate(uint16_t num, uint16_t limit, uint32_t base, uint8_t type, uint8_t gran)
{
    gdt_entries[num].base_low    = (base & 0xFFFF);
    gdt_entries[num].base_mid    = (base >> 16) & 0xFF;
    gdt_entries[num].base_high   = (base >> 24) & 0xFF;

    gdt_entries[num].limit_low   = (limit & 0xFFFF);
    gdt_entries[num].granularity = (limit >> 16) & 0x0F;

    gdt_entries[num].granularity |= gran & 0xF0;
    gdt_entries[num].access      = type;
}

void init_descriptor_tables()
{
    gdt_ptr.limit = (sizeof(gdt_entry_t) * 256) - 1;
    gdt_ptr.base = (uint32_t)&gdt_entries;

    write_descriptor_gate(0, 0, 0, 0, 0);
    write_descriptor_gate(1, 0xFFFFFFFF, 0, 0x9A, 0xCF);
    write_descriptor_gate(2, 0xFFFFFFFF, 0, 0x92, 0xCF);
    write_descriptor_gate(3, 0xFFFFFFFF, 0, 0xFA, 0xCF);
    write_descriptor_gate(4, 0xFFFFFFFF, 0, 0xF2, 0xCF);

    install_gdt((uint32_t)&gdt_ptr);
}