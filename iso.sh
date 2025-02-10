#!/bin/sh
make

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

mv kernel.elf isodir/boot/cuyos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "cuyos" {
	multiboot2 /boot/cuyos.kernel
}
EOF
grub2-mkrescue -o cuyos.iso isodir
