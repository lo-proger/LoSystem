

void kernel_main(void) {
    volatile unsigned short* video = 0xB8000;
    video[0] = (0x07 << 8) | 'H';
    video[1] = (0x07 << 8) | 'i';
    video[2] = (0x07 << 8) | '!';

    while(1) {
        __asm__ volatile ("hlt");
    }
}