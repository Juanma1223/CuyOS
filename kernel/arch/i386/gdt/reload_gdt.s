.text
.globl reloadGdt     # Export symbol for reloadGdt
.type reloadGdt, @function
reloadGdt:
    mov $0x10, %ebx 
    mov %ebx, %ds 
    mov %ebx, %es 
    mov %ebx, %fs 
    mov %ebx, %gs 
    mov %ebx, %ss 
    pop %edi 
    push $0x8
    push %edi
    retf     
