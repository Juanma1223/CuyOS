#include <kernel/idt.h>

// Create the IDT struct
struct IDTR idtr;

// Allocate space for all 256 entries for the IDT
struct InterruptDescriptor idt[IDT_MAX_DESCRIPTORS];

// This functions encodes an interruption vector into the IDT
void setIDTEntry(int vector, uint32_t base, uint16_t sel, uint8_t type_attr)
{
    if (vector == 1)
    {
        printf("Generic ISR: %i \n", base);
    }
    if (vector == 33)
    {
        printf("Keyboard ISR: %i \n", base);
    }

    idt[vector].offset_1 = base & 0xFFFF;         // Set offset bits 0..15
    idt[vector].selector = sel;                   // Set the code segment selector in GDT
    idt[vector].zero = 0;                         // Unused, set to 0
    idt[vector].type_attributes = type_attr;      // Set gate type, DPL, and P fields
    idt[vector].offset_2 = (base >> 16) & 0xFFFF; // Set offset bits 16..31
}

// Interruption Service Routines are defined on separate assembly files
extern void defaultInterruptHandler(void);
extern void keyboardInterruptHandler(void);
extern void timerInterruptHandler(void);

void load_idt()
{
    asm("lgdt %0" : : "m"(idtr));
}

void setupIDT()
{

    // Initialize each of the interruption vectors of the IDT
    for (int vector = 0; vector < IDT_MAX_DESCRIPTORS; vector++)
    {
        // Specific purpose IDT entries
        switch (vector)
        {
        case 32:
            setIDTEntry(vector, (uint32_t)defaultInterruptHandler, CODE_SEGMENT_SELECTOR, INTERRUPT_GATE32);
            break;
        case 33:
            // IRQ1 is the interrupt request line associated with the keyboard in a typical x86 system
            // IRQs 0-15 are mapped to interrupt vectors 32-47 (this is after the remapping of the PIC, where the PIC's IRQs are shifted to avoid conflicts with CPU exceptions).
            // Therefore, the keyboard inte rrupt, which is on IRQ1, will be placed at vector 33 in the IDT (since vectors start from 0, IRQ1 maps to 32 + 1 = 33).
            setIDTEntry(vector, (uint32_t)defaultInterruptHandler, CODE_SEGMENT_SELECTOR, INTERRUPT_GATE32);
            printf("Keyboard ISR Address: %p\n", defaultInterruptHandler);
            break;
        default:
            // Generic IDT entries
            // TODO: Define the purpose of each entry
            setIDTEntry(vector, (uint32_t)defaultInterruptHandler, CODE_SEGMENT_SELECTOR, INTERRUPT_GATE32);
            break;
        }
    }

    idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(struct InterruptDescriptor) * IDT_MAX_DESCRIPTORS - 1;

    load_idt();
    // Enable interrupts
    __asm__ __volatile__("sti");
}