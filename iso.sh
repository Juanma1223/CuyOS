#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/cuyos.kernel isodir/boot/cuyos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "cuyos" {
	multiboot /boot/cuyos.kernel
}
EOF
grub2-mkrescue -o cuyos.iso isodir
