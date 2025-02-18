.text
.global timerInterruptHandler
.type timerInterruptHandler, @function
timerInterruptHandler:
    # Push cpu context to the stack
    pusha
    push %ds
    push %es
    push %fs
    push %gs

    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    # Timer interruptionn will receive the stack pointer as the argument
    push %esp 

    # Call the C timer handler function
    call timerHandler

    # Replace the stack pointer with the value returned by timeHandler
    # In case the scheduler changed context, a new process context will be loaded
    mov %eax, %esp

    # Send End of Interrupt (EOI) signal to PIC
    mov $0x20, %al
    outb %al, $0x20

    pop %gs
    pop %fs
    pop %es
    pop %ds
    popa
    iret
