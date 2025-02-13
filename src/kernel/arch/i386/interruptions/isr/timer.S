.text
.global timerInterruptHandler
.type timerInterruptHandler, @function
timerInterruptHandler:
    # pusha
    # push %ds
    # push %es
    # push %fs
    # push %gs

    # mov $0x10, %ax
    # mov %ax, %ds
    # mov %ax, %es
    # mov %ax, %fs
    # mov %ax, %gs

    # Call the C timer handler function
    # call timerHandler

    # Send End of Interrupt (EOI) signal to PIC
    # mov $0x20, %al
    # outb %al, $0x20

    # pop %gs
    # pop %fs
    # pop %es
    # pop %ds
    # popa
    iret
