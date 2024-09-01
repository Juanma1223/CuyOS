#include <kernel/idt.h>

// Create the IDT struct
struct IDTR idtr;

// Allocate space for all 256 entries for the IDT
struct InterruptDescriptor idt[IDT_MAX_DESCRIPTORS];

// This functions encodes an interruption vector into the IDT
void setIDTEntry(int vector, uint32_t base, uint16_t sel, uint8_t type_attr)
{
    idt[vector].offset_1 = base & 0xFFFF;         // Set offset bits 0..15
    idt[vector].selector = sel;                   // Set the code segment selector in GDT
    idt[vector].zero = 0;                         // Unused, set to 0
    idt[vector].type_attributes = type_attr;      // Set gate type, DPL, and P fields
    idt[vector].offset_2 = (base >> 16) & 0xFFFF; // Set offset bits 16..31
}

void defaultInterruptHandler() {

}; // Declare your interrupt handler function
void keyboardInterruptHandler() {


}; // Example: handler for keyboard interrupts

void setupIDT()
{

    // TODO: Make this separate files and tidy code up
    // Assembler functions to handle interruptions

    // Initialize each of the interruption vectors of the IDT
    for (int i = 0; i < IDT_MAX_DESCRIPTORS; i++)
    {
        // Specific purpose IDT entries
        switch (i)
        {
        case 33:
            // Keyboard interrupt routine
            setIDTEntry(i, (uint32_t)keyboardInterruptHandler, CODE_SEGMENT_SELECTOR, INTERRUPT_GATE32);
            break;
        default:
            // Generic IDT entries
            // TODO: Define the purpose of each entry
            setIDTEntry(i, (uint32_t)defaultInterruptHandler, 0x08, INTERRUPT_GATE32);
            break;
        }
    }

    idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(struct InterruptDescriptor) * IDT_MAX_DESCRIPTORS - 1;

    extern void setIdt(struct IDTR * gdtPointer);
    setIdt(&idtr);
}