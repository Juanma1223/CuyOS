.section .data
.align 2

.text
.global keyboardInterruptHandler
.type keyboardInterruptHandler, @function
keyboardInterruptHandler:
    cli
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
    inb $0x60, %al                # Read the scancode from the keyboard into AX
    
    # For debugging, store scancode in %esi to check if handler is working
    mov %al, %bl                 # Store the scancode in %bl
    # mov $1, %ebx

    # Send End of Interrupt (EOI) signal to PIC
    mov $0x20, %al                # Load 0x20 into AL (EOI command)
    outb %al, $0x20               # Send EOI to the Master PIC (IRQ1 is in the Master PIC range)

    pop %gs                       # Restore segment registers
    pop %fs
    pop %es
    pop %ds
    popa                          # Restore general-purpose registers
    sti
    iret                          # Return from interrupt