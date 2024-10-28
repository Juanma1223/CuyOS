#include <kernel/io.h>
#include <stdio.h>
#include <stdint.h>

void setKeyboardScancode(int scancode)
{
    // Set scancode
    outb(0x60, 0xF0);
    io_wait();
    outb(0x60, scancode);
    int firstCode = inb(0x60);
    int secondeCode = inb(0x61);
}