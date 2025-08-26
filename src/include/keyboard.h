#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

#define MAX_KEYB_BUFFER_SIZE 255
#define SCANCODE_MAX 0x58 // Highest scancode value in set 1

typedef struct
{
    uint8_t code;
    uint8_t statusMask;
} keyEvent;

// Store all pressed keys up to 256, this struct holds useful information about the key pressed event
extern keyEvent keyboardBuffer[MAX_KEYB_BUFFER_SIZE];
extern char scancodeTable[SCANCODE_MAX + 1];

#endif