nasm -f bin boot.asm -o boot.bin

dd if=/dev/zero of=myos.hdd bs=512 count=20480>/dev/null

dd if=boot.bin of=myos.hdd bs=512 count=1 conv=notrunc 2>/dev/null

