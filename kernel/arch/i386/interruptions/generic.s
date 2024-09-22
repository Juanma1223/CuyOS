.section .data
.align 2

.text
.global defaultInterruptHandler
.type defaultInterruptHandler, @function
defaultInterruptHandler:
    # Send End of Interrupt (EOI) signal to PIC
    mov $0x20, %al                # Load 0x20 into AL (EOI command)
    outb %al, $0x20               # Send EOI to the Master PIC
    outb %al, $0xA0               # Send EOI to the Slave PIC (only for IRQs 8-15)
    iret                          # Return from interrupt