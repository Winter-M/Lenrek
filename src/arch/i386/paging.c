
# include <paging.h>

# define CHK_BIT(V, N)	((V) & (N))
# define SET_BIT(V, N)	((V) |= (N))
# define CLR_VIT(V, N)	((V) &= ~(N))

# define PDIDX(ADDR)	((ADDR) >> 22)
# define PTIDX(ADDR)	(((ADDR) >> 12) & 0x3FF)

# define FLAG_MASK	(0xFFF)

paddr_t paging_get_physical(vaddr_t addr, flags_t *flags) {
	int pdidx = PDIDX(addr);
	int ptidx = PTIDX(addr);

	paddr_t *pd = paging_get_pdir();
	if(!CHK_BIT(pd[pdidx], PD_PRESENT)) {
		return (paddr_t) -1;
	}

	paddr_t value;
	if(CHK_BIT(pd[pdidx], PD_LARGEPAGE)) {
		value = pd[pdidx];
	} else {
		paddr_t *pt = paging_get_ptable(pdidx);
		if(!CHK_BIT(pt[ptidx], PT_PRESENT)) {
			return (paddr_t)-1;
		}
	}
	
	if(flags) *flags = value & FLAG_MASK;
	return (value & ~FLAG_MASK) | (addr & FLAG_MASK);
}

paddr_t paging_map_page(vaddr_t addr0, paddr_t addr1, flags_t flags) {
	if((addr0 & FLAG_MASK) || (addr1 & FLAG_MASK)) {
		return (paddr_t)-1;
	}

	int pdidx = PDIDX(addr0);
	int ptidx = PTIDX(addr0);

	paddr_t *pd = paging_get_pdir();

	paddr_t value;
	if(CHK_BIT(flags, PD_LARGEPAGE)) {
		value = pd[pdidx];
		pd[pdidx] = addr1 | flags;
	} else {	
		if(!CHK_BIT(pd[pdidx], PD_PRESENT)) {
			// TODO : Map page table
			return (paddr_t)-1;
		}

		paddr_t *pt = paging_get_ptable(ptidx);
		value = pt[ptidx];
		pt[ptidx] = addr1 | flags;
	}

	return value;
}

