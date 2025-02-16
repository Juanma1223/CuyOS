#include <stdio.h>
#include <string.h>

#include <io.h>
#include <tty.h>
#include <gdt.h>
#include <idt.h>
#include <pic.h>
#include <keyboard_driver.h>
#include <screen_driver.h>

// Receive multiboot headers information
void kernelMain(void* multiboot_info_addr)
{
	terminal_initialize(); 
	init_framebuffer(multiboot_info_addr);
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
