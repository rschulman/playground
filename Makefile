CC=i686-elf-gcc
AS=nasm
CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra -c
ASFLAGS=-f elf
LDFLAGS=-ffreestanding -nostdlib -lgcc
SOURCES=kernel.c stdio.c boot.s set_gdt.s
OBJECTS=kernel.o stdio.o boot.o set_gdt.o
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
