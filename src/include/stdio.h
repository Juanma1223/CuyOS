#include <sys/cdefs.h>
#include <string.h>

#define EOF (-1)

int printf(const char* __restrict, ...);
int putchar(int);
int puts(const char*);
void terminal_write(const char *data, size_t size);
