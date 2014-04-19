CC=i686-elf-gcc
AS=nasm
CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra -c -g
ASFLAGS=-f elf
LDFLAGS=-ffreestanding -nostdlib -lgcc
SOURCES=kernel.c stdio.c descriptors.c interrupts.c boot.s set_gdt.s interrupt_handlers.s
OBJECTS=kernel.o stdio.o descriptors.o interrupts.o boot.o set_gdt.o interrupt_handlers.o
EXECUTABLE=playground.bin

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -T linker.ld $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

.s.o:
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm *.o
