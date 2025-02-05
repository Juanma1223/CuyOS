SRCDIR=src
OBJDIR=obj

CC=clang
AS=clang
LD=ld
TARGET=x86_64-elf
CFLAGS=-ffreestanding -nostdlib -mno-red-zone -Wall -Wextra -I $(SRCDIR)/include
LDFLAGS=-T src/kernel/arch/i386/linker.ld --nostdlib

SOURCES=$(shell find $(SRCDIR) -name "*.c" -o -name "*.s")
OBJECTS=$(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(SOURCES:.c=.o))


$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(dir $@)
	$(CC) --target=$(TARGET) $(CFLAGS) -c $< -o $@


$(OBJDIR)/%.o: $(SRCDIR)/%.s
	mkdir -p $(dir $@)
	$(AS) --target=$(TARGET) -c $< -o $@

kernel.elf: $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^

clean:
	rm -rf $(OBJDIR) kernel.elf

.PHONY: clean
