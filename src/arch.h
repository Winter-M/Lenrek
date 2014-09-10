# ifndef __LENREK_ARCH_H__
# define __LENREK_ARCH_H__

# ifdef _ARCH_I386
typedef short port_t;

__attribute__((always_inline, gnu_inline))
inline void interrupts(int state) {
	if(state) __asm__ __volatile__("sti");
	else __asm__ __volatile__("cli");
}

__attribute__((always_inline))
inline void io_wait() {
	extern void outb(port_t, char);
	outb(0x80, 0);
}
# endif /* i386 */

char inb(port_t port);
short inw(port_t port);
long inl(port_t port);

void outb(port_t port, char value);
void outw(port_t port, short value);
void outl(port_t port, long value);

# endif /* arch.h */

