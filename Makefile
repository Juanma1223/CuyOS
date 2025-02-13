SRCDIR=src
OBJDIR=obj

CC=clang
AS=as
LD=ld
TARGET=i386-elf
CFLAGS=-g -m32 -ffreestanding -nostdlib -mno-red-zone -Wall -Wextra -march=i386 -I $(SRCDIR)/include
LDFLAGS=-m elf_i386 -T src/kernel/arch/i386/linker.ld --nostdlib

# Find all source files
C_SOURCES=$(shell find $(SRCDIR) -name "*.c")
ASM_SOURCES=$(shell find $(SRCDIR) -name "*.s" -o -name "*.S")

# Generate object file paths
C_OBJECTS=$(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(C_SOURCES:.c=.o))
ASM_OBJECTS=$(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(ASM_SOURCES:.S=.o))

OBJECTS=$(C_OBJECTS) $(ASM_OBJECTS)

# Compilation rules
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(dir $@)
	$(CC) --target=$(TARGET) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.S
	mkdir -p $(dir $@)
	$(AS) --32 -c $< -o $@

# Linking
kernel.elf: $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^

# Cleanup
clean:
	rm -rf $(OBJDIR) kernel.elf

.PHONY: clean
