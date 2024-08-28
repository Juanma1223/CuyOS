.section .data
    .align 2

.text
.global setGdt
.type setGdt, @function
setGdt:
    lgdt (%esp)                   # Load the GDTR register with the GDT descriptor
    ret                           # Return from the function