#include <stdint.h>
#include <stdio.h>

struct InterruptDescriptor32 {
   uint16_t offset_1;        // offset bits 0..15
   uint16_t selector;        // a code segment selector in GDT or LDT
   uint8_t  zero;            // unused, set to 0
   uint8_t  type_attributes; // gate type, dpl, and p fields
   uint16_t offset_2;        // offset bits 16..31
};


// This struct holds the memory adresses of the all the interrupt descriptors
struct IDTR {
    uint16_t limit;
    uint32_t base;
};

void setupIDT();