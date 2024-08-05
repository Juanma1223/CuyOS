.section .data
    .align 2
gdtr:
    .word 0      # Limit (16 bits)
    .long 0      # Base (32 bits)

gdt:
    .quad 0x0000000000000000  # Null descriptor (mandatory)
    .quad 0x00CF9A000000FFFF  # Code segment descriptor
    .quad 0x00CF92000000FFFF  # Data segment descriptor
    .quad 0x0000000000000000  # Additional entry
gdt_end:

.text
.global setGdt
.type setGdt, @function
setGdt:
    xor %eax, %eax                        # Clear EAX register
    mov $gdt_end - gdt - 1, %ax           # Load GDT limit into AX
    mov %ax, gdtr                         # Store GDT limit in GDTR
    mov $gdt, %eax                        # Load GDT base address into EAX
    mov %eax, gdtr+2                      # Store GDT base address in GDTR
    lgdt gdtr                             # Load the GDTR register with the GDT descriptor
    ret                                   # Return from the function