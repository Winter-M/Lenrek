
# include <arch.h>

# define inx(x, t) \
	t in ## x (short port) { \
		t value = 0; \
		__asm__ __volatile__( \
			"in" #x " %1, %0" \
			: "=a"(value) \
			: "Nd"(port) \
		); \
		return value; \
	}

# define outx(x, t) \
	void out ## x (short port, t value) { \
		__asm__ __volatile__( \
			"out" #x " %0, %1" \
			:: "r"(value) \
			, "Nd"(port) \
		); \
	}

inx(b, char)
outx(b, char)

inx(w, short)
outx(w, short)

inx(l, long)
outx(l, long)

void io_wait() {
	outb(0x80, 0);
}

void gdt_install(void *gdt_descriptor) {
	__asm__("lgdt (%0)" : "r"(gdt_descriptor));
	__asm__("movl %0, %ds" : "a"(0x10));
	__asm__("movl %0, %es" : "a"(0x10));
	__asm__("movl %0, %fs" : "a"(0x10));
	__asm__("movl %0, %gs" : "a"(0x10));
	__asm__("movl %0, %ss" : "a"(0x10));
	__asm__("jmp $0x08, $gdt_install_end");

	__asm__("gdt_install_end:");
}

void idt_install(void *idt_descriptor) {
	__asm__("lidt (%0)" : "r"(idt_descriptor));
}

