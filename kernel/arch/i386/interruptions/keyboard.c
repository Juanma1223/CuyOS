#include <stdio.h>
#include <kernel/io.h>

void keyboardISR()
{
    int scancode = inb(0x60);
    // do_something_with_the_scancode(scancode);

    // Let's print the scancode we received for now
    printf("Scancode read: %p\n", scancode);
}
