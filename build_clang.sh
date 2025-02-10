FILES=$(find src -name "*.c" -o -name "*.S" -o -name "*.s")
CFLAGS="-ffreestanding -nostdlib -mno-red-zone -Wall -Wextra -I src/include -m32"

echo "Compiling..."

for f in $FILES
do
    clang --target=i386-elf -g -m32 -ffreestanding -nostdlib -mno-red-zone -Wall -Wextra -I src/include -c $f -o "$f.o"
done

echo "Moving files..."

BUILT_FILES=$(find src -name "*.o")
for f in $BUILT_FILES
do
    mv $f ./obj/
done

echo "Linking..."


ld -m elf_i386 -T src/kernel/arch/i386/linker.ld --nostdlib $(find obj -name "*.o") -o kernel.elf
mv kernel.elf isodir/boot
grub2-mkrescue -o cuyos.iso isodir
