#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <random.h>
#include <tty.h>
#include "screen_driver.h"
#include <keyboard.h>

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
int terminal_color = WHITE;
int command_color = GREEN;
static uint16_t *terminal_buffer;

// Buffer to store the last entered line
#define MAX_INPUT_LINE  (VGA_WIDTH + 1)
static char last_input_line[MAX_INPUT_LINE];

int strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char *)s1 - *(const unsigned char *)s2;
}


void terminal_initialize(void)
{
	terminal_row = 0;
	terminal_column = 0;
	for (size_t y = 0; y < VGA_HEIGHT; y++)
	{
		for (size_t x = 0; x < VGA_WIDTH; x++)
		{
			draw_char(' ', x, y,BLACK);
		}
	}
}

void terminal_setcolor(int color)
{
	terminal_color = color;
}

void terminal_putentryat(unsigned char c, int color, size_t x, size_t y)
{
	draw_char(c, x, y, color);
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
    // This is a line jump, a command is entered
    if (c == '\n')
    {
        terminal_row++;
        terminal_column = 0;

		// This logic is only used on the demostration, it should be moved to a different function or file

        // Save the characters from keyboardBuffer into last_input_line
        int idx = 0;
        for(int i = 0; i < VGA_WIDTH && idx < MAX_INPUT_LINE - 1; i++){
            char ch = scancodeTable[keyboardBuffer[i].code];
            if (ch != '\n' && ch != 0) {
                terminal_putentryat(ch, command_color, i, terminal_row);
                last_input_line[idx++] = ch;
            }
        }
        last_input_line[idx] = '\0'; // Null-terminate the string

        // Check if the entered line is "clear"
        if (strcmp(last_input_line, "clear") == 0) {
            terminal_initialize();
        }

		if (strcmp(last_input_line, "change") == 0) {
            if(terminal_color == WHITE){
				terminal_color = RED;
				command_color = MAGENTA;
			}else{
				terminal_color = WHITE;
				command_color = GREEN;
			}
        }

        clearKeyboardBuffer();
        terminal_row++;
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
