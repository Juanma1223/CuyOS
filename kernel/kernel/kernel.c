#include <stdio.h>
#include <string.h>

#include <kernel/tty.h>

void kernel_main(void)
{
	terminal_initialize();
	printf("Welcome to CuyOS! \n");
	printf("The operating system for you to learn! \n");
}
