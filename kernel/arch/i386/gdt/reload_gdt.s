.text
.globl reloadGdt     # Export symbol for reloadGdt
.type reloadGdt, @function
reloadGdt:
    mov $0x10, %eax 
    # mov %eax, %ss 
    mov %eax, %ds 
    mov %eax, %es 
    mov %eax, %fs 
    mov %eax, %gs 
    pop %ebx 
    push $0x8
    push %ebx
    retf     
