# ifndef __LENREK_PAGING_H__
# define __LENREK_PAGING_H__

# ifdef _PAGE_I386
#	define PAGE_BIT(N)	(1 << (N))
#	/* Page Directory Flags */
#	define PD_PRESENT	PAGE_BIT(0)
#	define PD_READWRITE	PAGE_BIT(1)
#	define PD_SUPERVISOR	PAGE_BIT(2)
#	define PD_WRITETHROUGH	PAGE_BIT(3)
#	define PD_NOCACHE	PAGE_BIT(4)
#	define PD_ACCESSED	PAGE_BIT(5)
#	define PD_RESERVED	PAGE_BIT(6)
#	define PD_LARGEPAGE	PAGE_BIT(7)
#	define PD_IGNORED	PAGE_BIT(8)
#	define PD_AVAILABLE0	PAGE_BIT(9)
#	define PD_AVAILABLE1	PAGE_BIT(10)
#	define PD_AVAILABLE2	PAGE_BIT(11)
#	/* Page Table Flags */
#	define PT_PRESENT	PAGE_BIT(0)
#	define PT_READWRITE	PAGE_BIT(1)
#	define PT_SUPERVISOR	PAGE_BIT(2)
#	define PT_WRITETHROUGH	PAGE_BIT(3)
#	define PT_NOCACHE	PAGE_BIT(4)
#	define PT_ACCESSED	PAGE_BIT(5)
#	define PT_DIRTY		PAGE_BIT(6)
#	define PT_RESERVED	PAGE_BIT(7)
#	define PT_GLOBAL	PAGE_BIT(8)
#	define PT_AVAILABLE0	PAGE_BIT(9)
#	define PT_AVAILABLE1	PAGE_BIT(10)
#	define PT_AVAILABLE2	PAGE_BIT(11)
#	/* Paging Types */
	typedef unsigned long	vaddr_t;
	typedef unsigned long	paddr_t;
	typedef unsigned long	flags_t;
#	/* Paging Functions */

inline vaddr_t *paging_get_pdir() {
	return (vaddr_t *)0xFFFFF000;
}

inline vaddr_t *paging_get_ptable(int idx) {
	return (vaddr_t *)0xFFC00000 + (0x400 * idx);
}

inline paddr_t paging_get_pdir_addr() {
	extern long read_cr3(void);
	return (paddr_t)read_cr3();
}

inline void paging_set_state(int state) {
	extern long read_cr3(void);
	extern void write_cr3(long);
	if(state) write_cr3(read_cr3() | PAGE_BIT(31));
	else write_cr3(read_cr3() & ~PAGE_BIT(31));
}

inline void paging_flush_page(vaddr_t addr) {
	__asm__ __volatile__(
		"invlpg (%0)"
		:: "r"(addr)
		: "memory"
	);
}

inline void paging_flush_all() {
	paging_set_state(0);
	paging_set_state(1);
}

# endif /* i386 */

paddr_t paging_get_physical(vaddr_t addr, flags *flags);

paddr_t paging_map_page(vaddr_t addr0, paddr_t addr1, flags_t flags);

# endif /* paging.h */

