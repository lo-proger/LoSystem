/*

LLLL           OOOOO      SSSS     Y       Y     SSSS
LLLL          OO   OO    SS   S     Y     Y     SS   S
LLLL          OO   OO     SS         Y   Y       SS
LLLL          OO   OO      SS         Y Y         SS
LLLL          OO   OO       SS         Y           SS
LLLLLLLLL     OO   OO    S   SS        Y        S   SS
LLLLLLLLL      OOOOO      SSSS         Y         SSSS

// Внутриядерные библиотеки \\
||    Библиотеки, которые    ||
||являются частью самого ядра||
\\         MEMORY.C         //

*/

#include "./memory.h"

gdt_struct_t create_gdt_struct(uint16_t limit_low, uint32_t base, uint8_t access, uint8_t granularity) {
    gdt_struct_t gdt_struct;
    // заполнение полей
    gdt_struct.limit_low = limit_low;
    gdt_struct.base_low = base & 0xFFFF;
    gdt_struct.base_middle = (base >> 16) & 0xFF;
    gdt_struct.access = access;
    gdt_struct.granularity = granularity;
    gdt_struct.base_high = (base >> 24) & 0xFF;

    return gdt_struct;
}

uint8_t create_gdt_access(bool ed_r, bool w_c, bool ex, bool dt, uint8_t DPL, bool p) {
    return (p << 7) | ((DPL & 0b11) << 5) | (dt << 4) | 
           (ex << 3) | (w_c << 2) | (ed_r << 1);
    // сдвигаем каждое значение на какое-то количество бит влево
}

uint8_t create_gdt_granularity(uint8_t limit_high, bool lm, bool db, bool g) {
    return ((limit_high & 0x0F) << 0) | (0 << 4) | (lm << 5) | (db << 6) | (g << 7);
}

gdt_pointer_t create_gdt_pointer(gdt_struct_t* gdt_array, uint16_t array_size) {
    gdt_pointer_t gdt_pointer;
    gdt_pointer.gdt_size = array_size * sizeof(gdt_struct_t) - 1; // в спецификации Intel значение равняется кол-во таблиц * размер таблицы - 1
    gdt_pointer.gdt_address = (uint32_t)gdt_array;

    return gdt_pointer;
}