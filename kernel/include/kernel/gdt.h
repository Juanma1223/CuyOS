#include <stdint.h>

// In this file we define functions and structs to interact with the Global Descriptor table

struct GDT_entry{
    int limit;
    int base;
    int access_byte;
    int flags;
};


void encodeGdtEntry(uint8_t *target, struct GDT_entry source);
void setupGDT();