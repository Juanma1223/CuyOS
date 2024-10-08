#include <stdint.h>
#include <stdio.h>
#include <kernel/gdt.h>

// In this file we define functions and structs to interact with the Global Descriptor table

// Create the new GDT base and limit pointers
// This are the memory adresses which hold memory segments needed for many purposes such as interruptions
// or user space applications
static struct GDTR gdtr;

// This are the segments within the GDT, these define segments of memory with specific purposes
struct GDT_entry gdt[GDT_DESCRIPTORS_QUANTITY];

// This function encodes a gdt entry into an 8 bytes binary structure
void encodeGdtEntry(uint8_t *target, struct GDT_entry source)
{
    // Check the limit to make sure that it can be encoded
    if (source.limit > 0xFFFFF)
    {
        printf("GDT cannot encode limits larger than 0xFFFFF");
    }



    // Encode the limit
    target[0] = 0xFFFFF & 0xFF;
    target[1] = (0xFFFFF >> 8) & 0xFF;
    target[6] = (0xFFFFF >> 16) & 0x0F;

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

void load_gdt()
{
    asm("lgdt %0" : : "m"(gdtr));
}

// Assembly function to initialize the Global Descriptor Table
void setupGDT()
{
    // Each segment has specific use cases and as such, each has it's own privilege level and flags
    struct GDT_entry nullSegment = {
        .limit = 0xFFFFF,
        .base = 0x00000000,
        .access_byte = 0x00,
        .flags = 0x0};
    // Start on position 1 because first position is used for the null segment
    encodeGdtEntry((uint8_t *)&gdt[0], nullSegment);

    struct GDT_entry kernel_code = {
        .limit = 0xFFFFF,    // 1 MB limit
        .base = 0x00000000,  // Base address 0
        .access_byte = 0x9A, // Code segment, present, DPL 0, executable, readable
        .flags = 0xCF        // 4 KB granularity, 32-bit protected mode
    };
    // Start on position 1 because first position is used for the null segment
    encodeGdtEntry((uint8_t *)&gdt[1], kernel_code);

    struct GDT_entry kernel_data = {
        .limit = 0xFFFFF,    // 1 MB limit
        .base = 0x00000000,  // Base address 0
        .access_byte = 0x92, // Data segment, present, DPL 0, writable
        .flags = 0xCF        // 4 KB granularity, 32-bit protected mode
    };
    encodeGdtEntry((uint8_t *)&gdt[2], kernel_data);

    // struct GDT_entry user_code = {
    //     .limit = 0xFFFFF,    // 1 MB limit
    //     .base = 0x00100000,  // Base address 0
    //     .access_byte = 0xFA, // Code segment, present, DPL 3, executable, readable
    //     .flags = 0xCF         // 4 KB granularity, 32-bit protected mode
    // };
    // encodeGdtEntry((uint8_t *)&gdt[3], user_code);

    // struct GDT_entry user_data = {
    //     .limit = 0xFFFFF,    // 1 MB limit
    //     .base = 0x00100000,  // Base address 0
    //     .access_byte = 0xF2, // Data segment, present, DPL 3, writable
    //     .flags = 0xCF         // 4 KB granularity, 32-bit protected mode
    // };
    // encodeGdtEntry((uint8_t *)&gdt[4], user_data);

    // GDT base is defined by the first memory address on the GDT entries table structure
    gdtr.base = (uintptr_t)&gdt[0];
    // Allocate as much space as GDT entries will be used, each entry is 8 bytes long
    gdtr.limit = (sizeof(struct GDT_entry) * GDT_DESCRIPTORS_QUANTITY) - 1;

    printf("GDT Base: %i\n", (void *)gdtr.base);
    printf("GDT Limit: %i\n", (void *)gdtr.limit);

    extern void reloadGdt();
    // This function is defined using assembler in set_gdt.s file
    // Using assembler it creates space to hold 4 segment descriptors
    load_gdt();
    reloadGdt();
}