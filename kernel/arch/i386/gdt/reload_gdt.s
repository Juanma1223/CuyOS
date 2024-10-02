.text
.globl reloadGdt     # Export symbol for reloadGdt
.type reloadGdt, @function
reloadGdt:
    # jmp $0x08,$reloadRegisters
# reloadRegisters:
    # Reload data segments with 0x10 (assuming 0x10 is the data segment selector)
     mov $0x10, %eax
     mov %eax, %ds      
    # mov %ax, %es      
    # mov %ax, %fs      
    # mov %ax, %gs      
    # mov %ax, %ss     

    # Continue execution here in the new code segment
    ret               
