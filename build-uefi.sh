BUILD_DIR="./build"
SRC_DIR="./src"
OUTPUT_IMAGE="myos1.hdd"

mkdir -p $BUILD_DIR

clang -target x86_64-unknown-elf -fno-stack-protector -fshort-wchar -mno-red-zone -I$SRC_DIR/gnu-efi/inc -c $SRC_DIR/boot-uefi.c -o $BUILD_DIR/boot-uefi.o

# Минимальная линковка
ld.lld -nostdlib -eefi_main $BUILD_DIR/boot-uefi.o -o $BUILD_DIR/main.efi -L"$SRC_DIR/gnu-efi/x86_64/gnuefi" -lgnuefi -L"$SRC_DIR/gnu-efi/x86_64/lib" -lefi
dd if=/dev/zero of=$OUTPUT_IMAGE bs=1M count=10

# Собирает .efi, но как собрать образ на тестах не получается, не видит. 

read