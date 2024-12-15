#include <stdio.h>
#include <string.h>

#include <kernel/io.h>
#include <kernel/tty.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/pic.h>
#include <kernel/keyboard_driver.h>
#include <kernel/screen_driver.h>

// Receive multiboot headers information
void kernelMain(uint32_t multiboot_info_addr)
{
	// terminal_initialize(); 
	parse_multiboot(multiboot_info_addr);
	printf("Welcome to CuyOS! \n");
	setupGDT();
	printf("GDT initialized correctly ! \n");
	setKeyboardScancode(2);
	printf("Keyboard scancode set initialized correctly ! \n");
	setupIDT();
	printf("IDT initialized correctly ! \n");
	PICRemap(0x20, 0x28);
	printf("PIC remapped correctly ! \n");

	while (1)
	{
		// Main kernel loop
		asm("hlt"); // Halt the CPU until the next interrupt
	}
}
