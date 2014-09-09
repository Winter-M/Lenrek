# ifndef __LENREK_CONSOLE_H__
# define __LENREK_CONSOLE_H__

# ifdef _CONSOLE_I386
enum console_color {
	// TODO
};
#	/* Console Pseudo Fucntions */
#	define console_supported()	1
#	define console_color()		1
#	define console_default_buffer()	0xB8000
#	define console_default_width()	80
#	define console_default_height()	25
# endif /* i386 */

void console_clear();

void console_write_char(char ch);

void console_write_string(const char *str);

void console_get_bounds(int *rows, int *cols);

void console_set_bounds(int rows, int cols);

void console_get_buffer(int *addr);

void console_set_buffer(int addr);

void console_get_color(char *back, char *fore);

void console_set_color(char back, char fore);

void console_get_cursor(int *row, int *col);

void console_set_cursor(int row, int col);

# endif /* console.h */

