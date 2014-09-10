# ifndef __LENREK_UTILS_H__
# define __LENREK_UTILS_H__

# ifdef _STR_UTILS

__attribute__((always_inline))
inline int memcmp(const void *m1, const void *m2, unsigned long ct) {
	if(!ct || m1 == m2) return 0;
	char *a = m1, *b = m2;
	while(ct--) {
		if(*a != *b) return *b - *a;
		a++; b++;
	}
	return 0;
}

__attribute__((always_inline))
inline void *memcpy(void *dst, const void *src, unsigned long ct) {
	if(!ct || dst == src) return dst;
	char *d = dst, *s = src;
	while(ct--) *d++ = *s++;
	return dst;
}

__attribute__((always_inline))
inline void *memset(void *dst, int value, unsigned long ct) {
	if(!ct) return dst;
	char *d = dst, v = value;
	while(ct--) *d++ = v;
	return dst;
}

__attribute__((always_inline))
inline char *strcat(char *dst, const char *src) {
	char *d = dst;
	while(*dst) *dst++;
	while(*src) *dst++ = *src++;
	return d;
}

__attribute__((always_inline))
inline int strcmp(const char *a, const char *b) {
	if(a == b) return 0;
	while(*a && *b) {
		if(*a != *b) return *b - *a;
		a++; b++;
	}
	return *b - *a;
}

__attribute__((always_inline))
inline int strncmp(const char *a, const char *b, unsigned long ct) {
	return memcmp(a, b, ct);
}

__attribute__((always_inline))
inline char *strcpy(char *dst, const char *src) {
	if(dst == src) return dst;
	char *d = dst;
	while(*src) *dst++ = *src++;
	return d;
}

__attribute__((always_inline))
inline int strlen(const char *str) {
	int len = 0;
	while(*str++) len++;
	return len;
}

# endif /* string utils */

# endif /* utils.h */

