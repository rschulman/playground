CC=i586-elf-gcc
AS=nasm
CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra -c
LDFLAGS=-ffreestanding -nostdlib -lgcc
NASMFLAGS=-felf
SOURCES=kernel.c stdio.c boot.asm set_gdt.asm idt.c idta.asm isr_wrapper.asm
OBJECTS=kernel.o stdio.o boot.o set_gdt.o idt.o idta.o isr_wrapper.o
EXECUTABLE=playground.bin

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -T linker.ld $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

%.o: %.asm
	$(AS) $(NASMFLAGS) $< -o $@