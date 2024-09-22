#include <stdio.h>
#include <string.h>

#include <kernel/tty.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/pic.h>

void kernelMain(void)
{
	terminal_initialize();
	printf("Welcome to CuyOS! \n");
	setupGDT();
	printf("GDT initialized correctly ! \n");
	setupIDT();
	printf("IDT initialized correctly ! \n");
	PICRemap(0x20, 0x28);
	printf("PIC remapped correctly ! \n");

	// Enable interrupts
	__asm__ __volatile__("sti");
	while (1)
	{
		// Main kernel loop
		__asm__ __volatile__("hlt"); // Halt the CPU until the next interrupt
	}
}
