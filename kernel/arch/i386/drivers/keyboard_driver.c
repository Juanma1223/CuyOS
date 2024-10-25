#include <kernel/io.h>
#include <stdio.h>

void setKeyboardScancode(int scancode)
{
    // Check keyboard scancode set
    outb(0x64, 0x20);
    int set = inb(0x60);

    printf("Keyboard is using set: %i", set);

    // Set keyboard scancode to 2
    outb(0x60,0xF00 + scancode);
    int firstCode = inb(0x64);
    printf("first code: %i",firstCode);
    int secondeCode = inb(0x64);
    printf("second code: %i",secondeCode);
}