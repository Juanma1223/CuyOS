.section .data
    .align 2
gdtr:
    .word 0     # Limit (16 bits)
    .long 0     # Base (32 bits)

# This are the segments in which the memory of the operating system is going to be partitioned
gdt:
    .quad 0x0000000000000000 # Null descriptor (mandatory)
    .quad 0x00CF9A000000FFFF # Code segment descriptor
    .quad 0x00CF92000000FFFF # Data segment descriptor
    .quad 0x0000000000000000 # Additional entry, can be TSS or other

.text
.global setGdt
.type setGdt, @function
setGdt:
    mov 16(%esp), %ax        # Load the limit (16-bit) from the stack into AX
    mov %ax, gdtr            # Store the limit in gdtr
    mov 20(%esp), %eax       # Load the base address (32-bit) from the stack into EAX
    mov %eax, gdtr+2         # Store the base address in gdtr
    lgdt gdtr                # Load the GDT using the GDTR register
    ret                      # Return from the function
