
# include <console.h>

# define VRAM	((char *)addr)
# define POS	((xpos + ypos * xlim) * 2)
static int addr = console_default_buffer();
static int xlim = console_default_width();
static int ylim = console_default_height();
static int xpos = 0, ypos = 0;
static int color = 0x0F;

void console_clear() {
	int pos = xpos = ypos = 0;
	for(; pos < ylim * xlim * 2; pos++) {
		VRAM[pos] = '\0';
	}
}

static inline void console_scroll() {
	if(ypos >= ylim) {
		int row, col;
		for(row = 0; row < ylim; row++) {
			int offset = row * xlim * 2;
			for(col = 0; col < xlim * 2; col++) {
				int pos = offset + col;
				if(row < ylim) {
					VRAM[pos] = VRAM[pos + (xlim * 2)];
				} else {
					VRAM[pos] = '\0';
				}
			}
		}
		ypos--;
	}
}

static inline void console_update() {
	extern void outb(short, char);
	outb(0x3D4, 0x0F);
	outb(0x3D5, (char)(POS & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (char)((POS >> 8) & 0xFF));
}

void console_write_char(char ch) {
	switch(ch) {
		case '\n':
			xpos = 0;
			ypos++;
			break;
		case '\t':
			xpos += 8 - (xpos % 8);
			break;
		case '\b':
			if(xpos > 0) {
				xpos -= 2;
			} else {
				if(ypos > 0) {
					xpos = xlim - 2;
					ypos--;
				}
			}
			VRAM[POS + 0] = '\0';
			VRAM[POS + 1] = color;
			break;
		default:
			VRAM[POS + 0] = ch;
			VRAM[POS + 1] = color;
			xpos += 2;
			break;
	}
	if(xpos >= xlim) {
		xpos -= xlim;
		ypos++;
	}
	console_scroll();
	console_update();
}

void console_write_string(const char *str) {
	if(!str) str = "NULL";
	while(*str) console_write_char(*str++);
}

void console_get_bounds(int *rows, int *cols) {
	if(rows) *rows = ylim;
	if(cols) *cols = xlim;
}

void console_set_bounds(int rows, int cols) {
	ylim = rows;
	xlim = cols;
}

void console_get_buffer(int *_addr) {
	if(_addr) *_addr = addr;
}

void console_set_buffer(int _addr) {
	addr = _addr;
}

void console_get_color(char *back, char *fore) {
	if(back) *back = color >> 4;
	if(fore) *fore = color & 0xF;
}

void console_set_color(char back, char fore) {
	color = ((back << 4) & 0xF) | (fore & 0xF);
}

void console_get_cursor(int *row, int *col) {
	if(row) *row = ypos;
	if(col) *col = xpos;
}

void console_set_cursor(int row, int col) {
	ypos = row;
	xpos = col;
}

