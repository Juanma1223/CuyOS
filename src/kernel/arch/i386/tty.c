#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <random.h>
#include <tty.h>
#include "vga.h"
#include "screen_driver.h"

// This file defines the terminal functionality, in this case, using VGA buffer directly

// This is calculated as follows: framebuffer width/font width
static const size_t VGA_WIDTH = 60;
// This is calculated as follows: framebuffer heigth/font heigth
static const size_t VGA_HEIGHT = 25;
// 0xB8000 Is the reference to the VGA memory buffer
// If you write characters from this point, they will be shown in the terminal
// Each character takes 8 bytes
static uint16_t *const VGA_MEMORY = (uint16_t *)0xB8000;

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t *terminal_buffer;

void terminal_initialize(void)
{
	terminal_row = 0;
	terminal_column = 0;
	for (size_t y = 0; y < VGA_HEIGHT; y++)
	{
		for (size_t x = 0; x < VGA_WIDTH; x++)
		{
			draw_char(' ', x, y);
		}
	}
}

void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}

void terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y)
{
	draw_char(c, x, y);
}

void terminal_putchar(char c)
{
	// If terminal has reached maximum rows, reset it
	if (terminal_row >= VGA_HEIGHT)
	{
		terminal_initialize();
	}
	unsigned char uc = c;
	// This is a backspace
	if (c == '\b')
	{
		terminal_delete();
		return;
	}
	// This is a line jump
	if (c == '\n')
	{
		terminal_row++;
		terminal_column = 0;
		return;
	}
	terminal_putentryat(uc, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH)
	{
		terminal_column = 0;
		terminal_row++;
	}
}

void terminal_delete()
{
	if (terminal_column > 0)
	{
		terminal_column--;
		terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);
	}
}

void terminal_write(const char *data, size_t size)
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char *data)
{
	terminal_write(data, strlen(data));
}
