#include <stdio.h>
#include <kernel/io.h>
#include <stdbool.h>

#define MAX_KEYB_BUFFER_SIZE 255

// Scancode constants
#define PREFIX_SCANCODE 0xE0
#define BREAK_MASK 0x80
// Masks for modifiers
#define CTRL_MASK 1
#define ALT_MASK 2
#define SHIFT_MASK 3

// This 8 bit variable holds modifiers in case they have been applied
uint8_t currentModifiers = 0;

// Store all pressed keys up to 256, this struct holds useful information about the key pressed event
typedef struct
{
    uint8_t code;
    uint8_t statusMask;
} keyEvent;

keyEvent keyboardBuffer[MAX_KEYB_BUFFER_SIZE];
uint8_t buffPosition = 0;

// This function applies a modifier in case the scancode represents one
bool applyModifier(int scancode)
{
    switch (scancode)
    {
    case 0x1D:
        /* Ctrl modifier applied */
        currentModifiers |= 1 << CTRL_MASK;
        printf("Applied ctrl modifier \n");
        return true;
    case 0x38:
        currentModifiers |= 1 << ALT_MASK;
        printf("Applied alt modifier \n");
        return false;
    default:
        return false;
    }
}

bool removeModifier(int scancode)
{
    scancode -= BREAK_MASK;
    switch (scancode)
    {
    case 0x1D:
        /* Ctrl modifier applied */
        currentModifiers &= ~(1 << CTRL_MASK);
        printf("Removed ctrl modifier \n");
        return true;
    case 0x38:
        currentModifiers &= ~(1 << ALT_MASK);
        printf("Removed alt modifier \n");
        return false;
    default:
        return false;
    }
}

void keyboardDriver()
{
    int scancode = inb(0x60);
    // do_something_with_the_scancode(scancode);

    // Let's print the scancode we received for now
    printf("Scancode read: %p\n", scancode);

    if ((scancode & BREAK_MASK) == 0)
    {
        // This is a make code
        if (!applyModifier(scancode))
        {
            // If the key is not a modifier, save the event
            keyboardBuffer[buffPosition].code = scancode;
            keyboardBuffer[buffPosition].statusMask = currentModifiers;
            buffPosition = (buffPosition + 1) % MAX_KEYB_BUFFER_SIZE;
        }
    }
    else
    {
        // This is a break code
        removeModifier(scancode);
    }
}