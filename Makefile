CC=i586-elf-gcc
AS=i586-elf-as
CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra -c
LDFLAGS=-ffreestanding -nostdlib -lgcc
SOURCES=kernel.c boot.s
OBJECTS=kernel.o boot.o
EXECUTABLE=playground.bin

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -T linker.ld $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

.s.o:
	$(AS) $< -o $@