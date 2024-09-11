#include <stdint.h>
#include <stdio.h>

#define IDT_MAX_DESCRIPTORS 256
#define TASK_GATE16 0x5
#define INTERRUPT_GATE16 0x6
#define TRAP_GATE 0x7
#define INTERRUPT_GATE32 0xE
#define TRAP_GATE 0xF
// This is the entry of the code segment on the GDT
#define CODE_SEGMENT_SELECTOR 0x8

struct InterruptDescriptor
{
    uint16_t offset_1;       // offset bits 0..15
    uint16_t selector;       // a code segment selector in GDT or LDT
    uint8_t zero;            // unused, set to 0
    uint8_t type_attributes; // gate type, dpl, and p fields
    uint16_t offset_2;       // offset bits 16..31
};

// This struct holds the memory adresses of the all the interrupt descriptors
struct IDTR
{
    uint16_t limit;
    uint32_t base;
};

void setupIDT();
void setIDTEntry(int vector, uint32_t base, uint16_t sel, uint8_t type_attr);
void setIdt(struct IDTR * gdtPointer);
void defaultInterruptHandler();  // Declare your interrupt handler function
void keyboardInterruptHandler(); // Handler for keyboard interrupts