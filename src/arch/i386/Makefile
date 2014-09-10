
AS = i586-elf-as
CC = i586-elf-gcc

CFLAGS = -O2 -ffreestanding -I ../.. -D _PAGE_I386 -D _CONSOLE_I386 -D _ARCH_I386

all : libarch.a

.PHONY : clean
clean :
	rm -f libarch.a

libarch.a : libarch.a(arch.o console.o gdt.o idt.o paging.o)

