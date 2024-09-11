# Makefile

C_SOURCES = kernel.c isr.c idt.c gdt.c string.c keyboard.c cli.c timer.c fs.c process.c test_process.c
HEADERS = kernel.h isr.h idt.h gdt.h string.h keyboard.h cli.h timer.h fs.h process.h

OBJS = ${C_SOURCES:.c=.o} boot.o

CFLAGS = -m32 -ffreestanding -nostdlib -fno-builtin -fno-stack-protector
LDFLAGS = -m elf_i386

all: os-image

os-image: bootloader.bin kernel.bin
	cat bootloader.bin kernel.bin > os-image.bin

bootloader.bin: bootloader.asm
	nasm -f bin bootloader.asm -o bootloader.bin

kernel.bin: ${OBJS}
	ld $(LDFLAGS) -T link.ld -o kernel.bin ${OBJS}

%.o: %.c ${HEADERS}
	gcc $(CFLAGS) -c $< -o $@

boot.o: bootloader.asm
	nasm -f elf32 bootloader.asm -o boot.o

clean:
	rm -f *.bin *.o os-image.bin
