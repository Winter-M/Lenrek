
struct gdt_entry {
	short limit0;
	short base0;
	char  base1;
	char  access;
	char  limit1 : 4;
	char  flags  : 4;
	char  base2;
} __attribute__((packed));

struct gdt_descr {
	short size;
	int   offset;
} __attribute__((packed));

struct gdt_entry gdt_block[16];
struct gdt_descr gdt_descriptor;

void gdt_set_entry(int entry_id, unsigned long start_addr, unsigned long limit, short flags) {
	struct gdt_entry *entry = &gdt_block[entry_id];
	entry->base0 = (short)(start_addr & 0xFFFF);
	entry->base1 = (char)((start_addr >> 16) & 0xFF);
	entry->base2 = (char)((start_addr >> 24) & 0xFF);
	entry->limit0 = (short)(limit & 0xFFFF);
	entry->limit1 = (char)((limit >> 16) & 0xF);
	entry->access = (char)(flags & 0xFF);
	entry->flags = (char)((flags >> 8) & 0xF);
}

void gdt_commit(int entries) {
	extern void gdt_install(void *);
	gdt_descriptor.size = entries * sizeof(struct gdt_entry) - 1;
	gdt_descriptor.offset = (int)gdt_block;
	gdt_install(&gdt_descriptor);
}

