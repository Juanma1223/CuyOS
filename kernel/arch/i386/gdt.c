#include <stdint.h>
#include <stdio.h>

// In this file we define functions and structs to interact with the Global Descriptor table

struct GDT_entry
{
    int limit;
    int base;
    int access_byte;
    int flags;
};

// This function is used to define a segment inside the Global Descriptor Table
void encodeGdtEntry(uint8_t *target, struct GDT_entry source)
{
    // Check the limit to make sure that it can be encoded
    if (source.limit > 0xFFFFF)
    {
        printf("GDT cannot encode limits larger than 0xFFFFF");
    }

    // Encode the limit
    target[0] = source.limit & 0xFF;
    target[1] = (source.limit >> 8) & 0xFF;
    target[6] = (source.limit >> 16) & 0x0F;

    // Encode the base
    target[2] = source.base & 0xFF;
    target[3] = (source.base >> 8) & 0xFF;
    target[4] = (source.base >> 16) & 0xFF;
    target[7] = (source.base >> 24) & 0xFF;

    // Encode the access byte
    target[5] = source.access_byte;

    // Encode the flags
    target[6] |= (source.flags << 4);
}

// Assembly function to initialize the Global Descriptor Table
void setupGDT()
{
    extern void setGdt();
    uint32_t gdt_base = 0x0;
    uint16_t gdt_limit = (4 * 8) - 1; // 4 entries, each 8 bytes, minus 1
    // This function is defined using assembler in set_gdt.s file
    setGdt(gdt_limit, gdt_base);
}