#include <stdio.h>
#include <string.h>

#include <io.h>
#include <tty.h>
#include <gdt.h>
#include <idt.h>
#include <pic.h>
#include <keyboard_driver.h>
#include <screen_driver.h>
#include <scheduler.h>

void idle_main(void *arg)
{
	while (1)
	{
		asm("hlt");
	}
}

void test_process1()
{
	while (1)
	{
		printf("Process1 \n");
	}
}

void test_process2()
{
	while (1)
	{
		printf("Process2 \n");
	}
}

// Receive multiboot headers information
void kernelMain(void *multiboot_info_addr)
{
	// terminal_initialize();
	// create_process("Idle", *idle_main, NULL);
	init_framebuffer(multiboot_info_addr);
	printf("Welcome to CuyOS! \n");
	setupGDT();
	printf("GDT initialized correctly ! \n");
	setKeyboardScancode(2);
	printf("Keyboard scancode set initialized correctly ! \n");
	create_process("Process 1", *test_process1, NULL);
	create_process("Process 2", *test_process2, NULL);
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