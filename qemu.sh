#!/bin/sh
set -e
. ./iso.sh

# qemu-system-$(./target-triplet-to-arch.sh $HOST) -cdrom cuyos.iso

# Used while debugging
qemu-system-$(./target-triplet-to-arch.sh $HOST) -kernel ./kernel/cuyos.kernel -monitor stdio
