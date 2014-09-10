
struct idt_entry {
	short offset0;
	short selector;
	char  zero;
	char  attr;
	short offset1;
} __attribute__((packed));

struct idt_descr {
	short limit;
	int   base;
} __attribute__((packed));

struct idt_entry idt_block[256];
struct idt_descr idt_descriptor;

void idt_set_entry(int intr_id, void *handler, short selector, char attr) {
	struct idt_entry *entry = &idt_block[intr_id];
	entry->offset0 = (short)((int)handler & 0xFFFF);
	entry->offset1 = (short)(((int)handler >> 16) & 0xFFFF);
	entry->selector = selector;
	entry->attr = attr;
	entry->zero = 0;
}

void idt_commit(int entries) {
	extern void idt_install(void *);
	idt_descriptor.limit = entries * sizeof(struct idt_entry) - 1;
	idt_descriptor.base = (int)idt_block;
	idt_install(&idt_descriptor);
}

