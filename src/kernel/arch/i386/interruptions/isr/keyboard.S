.section .data
.align 2

.text
.global keyboardInterruptHandler
.type keyboardInterruptHandler, @function
keyboardInterruptHandler:
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

    call keyboardDriver
    # Interrupt handling logic
    ; inb $0x60, %al                # Read the scancode from the keyboard into AL
    
    # Move scancode to EBX for debugging
    ; movzx %al, %ebx               # Zero-extend the AL into EBX, ensuring EBX reflects the scancode

    # Send End of Interrupt (EOI) signal to PIC
    mov $0x20, %al                # Load 0x20 into AL (EOI command)
    outb %al, $0x20               # Send EOI to the Master PIC (IRQ1 is in the Master PIC range)

    pop %gs                       # Restore segment registers
    pop %fs
    pop %es
    pop %ds
    popa                          # Restore general-purpose registers
    iret                          # Return from interrupt