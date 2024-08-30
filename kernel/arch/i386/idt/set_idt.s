.section .data
    .align 2

.text
.global setIdt
.type setIdt, @function
setGdt:
    lidt (%esp)                   # Load the IDTR register with the IDT descriptor
    ret                           # Return from the function