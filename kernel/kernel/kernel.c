#include <stdio.h>
#include <string.h>

#include <kernel/io.h>
#include <kernel/tty.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/pic.h>
#include <kernel/keyboard_driver.h>

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

	setKeyboardScancode(2);

	while (1)
	{
		// Main kernel loop
		asm("hlt"); // Halt the CPU until the next interrupt
	}
}
