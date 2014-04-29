static inline void outb (uint16_t port, uint8_t value)
{
    asm volatile ( "outb %0, %1" : : "a"(value), "Nd"(port) );
}

static inline uint8_t inb (uint16_t port)
{
    uint8_t ret;
    asm volatile ( "inb %0, %1" : : "=a"(ret), "Nd"(port) );
    return ret;
}

static inline void io_wait ()
{
    asm volatile ("inb %0, $0x80" : : "a"(0) );
}