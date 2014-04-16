CC=i686-elf-gcc
AS=nasm
CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra -c
ASFLAGS=-f elf
LDFLAGS=-ffreestanding -nostdlib -lgcc
SOURCES=kernel.c stdio.c boot.asm set_gdt.asm
OBJECTS=kernel.o stdio.o boot.o set_gdt.o
SUFFIXES=.c .asm .o
EXECUTABLE=playground.bin

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -T linker.ld $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

.asm.o:
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm *.o
