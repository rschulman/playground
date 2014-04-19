typedef struct gdt_entry {
    uint16_t    limit_low;
    uint16_t    base_low;
    uint8_t     base_mid;
    uint8_t     access;
    uint8_t     granularity;
    uint8_t     base_high;
} __attribute__((packed)) gdt_entry_t;

typedef struct GDT {
    uint16_t limit;
    uint32_t base;
}__attribute__((packed)) GDT_t;

void init_descriptor_tables();