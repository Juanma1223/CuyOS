#include <stdint.h>
#include <pic.h>
#include <io.h>

// This function should be called when an interruption routine service has finished
// to inform the PIC it can receive other interruptions
void PICSendEOI(uint8_t irq)
{
    // If the IRQ is greater than 8, we are refering to the Slave PIC
    if (irq >= 8)
        outb(PIC2_COMMAND, PIC_EOI);

    outb(PIC1_COMMAND, PIC_EOI);
}

/*
arguments:
    offset1 - vector offset for master PIC
        vectors on the master become offset1..offset1+7
    offset2 - same for slave PIC: offset2..offset2+7
*/
void PICRemap(int offset1, int offset2)
{
    uint8_t a1, a2;

    // Save current PICs masks to restore them later
    a1 = inb(PIC1_DATA);
    a2 = inb(PIC2_DATA);

    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4); // starts the initialization sequence (in cascade mode)
    io_wait();
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    outb(PIC1_DATA, offset1); // ICW2: Master PIC vector offset
    io_wait();
    outb(PIC2_DATA, offset2); // ICW2: Slave PIC vector offset
    io_wait();
    outb(PIC1_DATA, 4); // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
    io_wait();
    outb(PIC2_DATA, 2); // ICW3: tell Slave PIC its cascade identity (0000 0010)
    io_wait();

    outb(PIC1_DATA, ICW4_8086); // ICW4: have the PICs use 8086 mode (and not 8080 mode)
    io_wait();
    outb(PIC2_DATA, ICW4_8086);
    io_wait();

    outb(PIC1_DATA, a1); // restore saved masks.
    outb(PIC2_DATA, a2);

    // Enable interrupts
    asm("sti");
}