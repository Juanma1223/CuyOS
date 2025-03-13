.text
.global timerInterruptHandler
.type timerInterruptHandler, @function
timerInterruptHandler:
    # Push CPU context to the stack
    pusha  # Save general-purpose registers

    # mov $0x10, %ax
    # mov %ax, %ds
    # mov %ax, %es
    # mov %ax, %fs
    # mov %ax, %gs

    # Pass the current stack pointer (pointer to cpu_status_t) to C function
    push %esp 
    call timerHandler


    # Replace the stack pointer with the value returned by timerHandler
    mov %eax, %esp  # %eax contains the new CPU context pointer

    # Restore new CPU context from the new process
    popa  # Restore general-purpose registers from the new ESP

    # Send End of Interrupt (EOI) signal to PIC
    mov $0x20, %al
    outb %al, $0x20  # Notify PIC that the interrupt has been handled
    
    # Return to the new process
    iret
