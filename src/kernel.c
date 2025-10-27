#include <stddef.h>

void kernel_main(void) {
    volatile unsigned short* video = (volatile unsigned short*)0xB8000;

    for (size_t i = 0; i < 1999; i++) {
        video[i] = (0x07 << 8) | ' ';
    }
    
    video[0] = (0x07 << 8) | 'H';
    video[1] = (0x07 << 8) | 'i';
    video[2] = (0x07 << 8) | '!';

    while(1) {
        __asm__ volatile("hlt");
    }
}