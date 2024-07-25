#include <stdio.h>
#include <string.h>

#include <kernel/tty.h>
#include <kernel/gdt.h>

void kernel_main(void)
{
	terminal_initialize();
	printf("Welcome to CuyOS! \n");
	// Assembly function to initialize the Global Descriptor Table
	setupGDT();
	printf("GDT initialized correctly !");
}
