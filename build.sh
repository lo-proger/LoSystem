BUILD_DIR="./build"
SRC_DIR="./src"
OUTPUT_IMAGE="myos.hdd"

mkdir $BUILD_DIR

nasm -f bin $SRC_DIR/boot.asm -o $BUILD_DIR/boot.bin

nasm -f elf32 $SRC_DIR/kernel_asm.asm -o $BUILD_DIR/kernel_asm.o

clang -target i386-pc-none -m32 -ffreestanding -nostdlib -O1 -c $SRC_DIR/kernel.c -o $BUILD_DIR/kernel.o

ld.lld -m elf_i386 -T linker.ld -nostdlib $BUILD_DIR/kernel_asm.o $BUILD_DIR/kernel.o -o $BUILD_DIR/kernel.elf

llvm-objcopy -O binary $BUILD_DIR/kernel.elf $BUILD_DIR/kernel.bin

dd if=/dev/zero of=myos.hdd bs=512 count=20480>/dev/null

dd if=$BUILD_DIR/boot.bin of=myos.hdd bs=512 count=1 conv=notrunc 2>/dev/null

dd if=$BUILD_DIR/kernel.bin of=myos.hdd bs=512 seek=1 conv=notrunc 2>/dev/null

rm -r $BUILD_DIR
read


