.section .mb2_hdr

# multiboot2 header: magic number, mode, length, checksum
mb2_hdr_begin:
.long 0xE85250D6
.long 0
.long (mb2_hdr_end - mb2_hdr_begin)
.long -(0xE85250D6 + (mb2_hdr_end - mb2_hdr_begin))

# framebuffer tag: type = 5
.align 8
framebuffer_tag_start:
    .short 0x05  # Type: framebuffer
    .short 0x01  # Optional tag
    .long 0x20  # Size
    .long 0  # Width - if 0, let the bootloader decide
    .long 0  # Height - same as above
    .long 0  # Depth  - same as above
framebuffer_tag_end:
.align 8

# the end tag: type = 0, size = 8
.long 0x0
.long 0x08
mb2_hdr_end:

.section .data
boot_stack_base:
    .word 0x1000

# backup the address of mb2 info struct, since ebx may be clobbered
.section .mb_text
    mov %ebx, %edi

    # setup a stack, and reset flags
    mov $(boot_stack_base + 0x1000), %esp
    pushl $0x2
    popf


# The kernel entry point.
.section .text
.global _start
.type _start, @function
_start:
	# Call the global constructors.
	call _init

	# Transfer control to the main kernel.
	call kernelMain

	# Hang if kernelMain unexpectedly returns.
	cli
1:	hlt
	jmp 1b
.size _start, . - _start
