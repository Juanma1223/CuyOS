#include <stdio.h>
#include <io.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_KEYB_BUFFER_SIZE 255
// Scancode constants
#define PREFIX_SCANCODE 0xE0
#define BREAK_MASK 0x80
#define SCANCODE_MAX 0x58 // Highest scancode value in set 1
// Masks for modifiers
#define CTRL_MASK 1
#define ALT_MASK 2
#define SHIFT_MASK 3

// Lookup table for scancode set 1 (values represent ASCII or custom kernel codes)
char scancodeTable[SCANCODE_MAX + 1] = {
    [0x00] = 0,  // Null (no key)
    [0x01] = 27, // ESC
    [0x02] = '1',
    [0x03] = '2',
    [0x04] = '3',
    [0x05] = '4',
    [0x06] = '5',
    [0x07] = '6',
    [0x08] = '7',
    [0x09] = '8',
    [0x0A] = '9',
    [0x0B] = '0',
    [0x0C] = '-',
    [0x0D] = '=',
    [0x0E] = '\b', // Backspace
    [0x0F] = '\t', // Tab
    [0x10] = 'q',
    [0x11] = 'w',
    [0x12] = 'e',
    [0x13] = 'r',
    [0x14] = 't',
    [0x15] = 'y',
    [0x16] = 'u',
    [0x17] = 'i',
    [0x18] = 'o',
    [0x19] = 'p',
    [0x1A] = '[',
    [0x1B] = ']',
    [0x1C] = '\n', // Enter
    [0x1D] = 0,    // Left Ctrl (non-ASCII control code)
    [0x1E] = 'a',
    [0x1F] = 's',
    [0x20] = 'd',
    [0x21] = 'f',
    [0x22] = 'g',
    [0x23] = 'h',
    [0x24] = 'j',
    [0x25] = 'k',
    [0x26] = 'l',
    [0x27] = ';',
    [0x28] = '\'',
    [0x29] = '`',
    [0x2A] = 0, // Left Shift
    [0x2B] = '\\',
    [0x2C] = 'z',
    [0x2D] = 'x',
    [0x2E] = 'c',
    [0x2F] = 'v',
    [0x30] = 'b',
    [0x31] = 'n',
    [0x32] = 'm',
    [0x33] = ',',
    [0x34] = '.',
    [0x35] = '/',
    [0x36] = 0, // Right Shift
    [0x37] = '*',
    [0x38] = 0, // Left Alt
    [0x39] = ' ',
    [0x3A] = 0, // Caps Lock
    [0x3B] = 0, // F1
    [0x3C] = 0, // F2
    [0x3D] = 0, // F3
    [0x3E] = 0, // F4
    [0x3F] = 0, // F5
    [0x40] = 0, // F6
    [0x41] = 0, // F7
    [0x42] = 0, // F8
    [0x43] = 0, // F9
    [0x44] = 0, // F10
    [0x45] = 0, // Num Lock
    [0x46] = 0, // Scroll Lock
    // Additional scancodes (e.g., arrow keys) would go here if needed
};

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
    if ((scancode & BREAK_MASK) == 0)
    {
        // This is a make code
        if (!applyModifier(scancode))
        {
            // If the key is not a modifier, save the event
            keyboardBuffer[buffPosition].code = scancode;
            keyboardBuffer[buffPosition].statusMask = currentModifiers;
            buffPosition = (buffPosition + 1) % MAX_KEYB_BUFFER_SIZE;
            printf("%c", scancodeTable[scancode]);
        }
    }
    else
    {
        // This is a break code
        removeModifier(scancode);
    }
}