.section text
.global defaultInterruptHandler
defaultInterruptHandler:
    pusha                         # Save all general-purpose registers
    push %ds                      # Save data segment register
    push %es
    push %fs
    push %gs

    mov $0x10, %ax                # Load the kernel data segment selector into AX
    mov %ax, %ds                  # Set DS to the kernel data segment
    mov %ax, %es                  # Set ES to the kernel data segment
    mov %ax, %fs                  # Set FS to the kernel data segment
    mov %ax, %gs                  # Set GS to the kernel data segment

    # Interrupt handling logic goes here
    # For example, code to handle a specific interrupt like keyboard input or timer

    # Send End of Interrupt (EOI) signal to PIC
    mov $0x20, %al                # Load 0x20 into AL (EOI command)
    outb %al, $0x20               # Send EOI to the Master PIC
    outb %al, $0xA0               # Send EOI to the Slave PIC (only for IRQs 8-15)

    pop %gs                       # Restore segment registers
    pop %fs
    pop %es
    pop %ds
    popa                          # Restore general-purpose registers
    iret                          # Return from interrupt