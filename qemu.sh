#!/bin/sh
set -e
. ./iso.sh

# qemu-system-$(./target-triplet-to-arch.sh $HOST) -cdrom cuyos.iso

# Used while debugging
# qemu-system-$(./target-triplet-to-arch.sh $HOST) -kernel ./kernel/cuyos.kernel -monitor stdio -s -S -machine type=pc-i440fx-3.1
# qemu-system-$(./target-triplet-to-arch.sh $HOST) -kernel ./kernel/cuyos.kernel -monitor stdio -s
qemu-system-i386 -boot d -cdrom ./cuyos.iso -monitor stdio -s