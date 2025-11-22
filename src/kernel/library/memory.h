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
\\     KERNEL.H      //

*/

#ifndef LOSYS_KERNELIB_MEMORY_H
#define LOSYS_KERNELIB_MEMORY_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint16_t limit_low; // указывает сколько памяти начиная с base может использовать процесс
    uint16_t base_low; // указывает адрес в памяти
    uint8_t base_middle; // продолжение base_low
    uint8_t access; // флаги p, dpl, s, type, (e, w) - type->3 = 0, (c, r) - type->3 = 1
    uint8_t granularity; 
    uint8_t base_high; // продолжение base_middle
} __attribute__((packed)) gdt_struct_t;

typedef struct {
    uint16_t gdt_size;     // Размер GDT (в байтах - 1)
    uint32_t gdt_address;  // Адрес GDT в памяти
} __attribute__((packed)) gdt_pointer_t;


/*
    От старшего к младшему, т.е. в 0b100000000 - 1 это 7 бит(старший), а в 0b000000001 - 1 это 0 бит(младший)

    gdt_struct::access -
    7 бит>>present->сегмент отсутствует в памяти=0, присутствует=1
    6-5 бит>>DPL(ring)->максимальные привилегии=00,ring 1=01, ring 2=10, минимальные привилегии=11
    4 бит>>descriptor type->системный сегмент=0, обычный=1
    3 бит>>executable->не исполняемый=0, исполняемый=1

    Если 3 бит = 0, то
    2 бит>>expansion direction->cегмент растёт вверх (обычные данные)=0, cегмент растёт вниз (стек)=1
    1 бит>>writable->чтение=0, чтение и запись=1
    Иначе
    2 бит>>сonforming->выполнение только с того же уровня ring=0, выполнение с других уровней ring=1
    1 бит>>readable->только выполнение=0, можно читать=1

    0 бит>>accessed - cpu устанавливает

    gdt_struct::granularity -
    7 бит>>granularity->лимит измеряется в байтах (1 байт)=0, лимит измеряется в страницах по 4КБ (4096 байт)=1
    Если для сегментов кода, то
    6 бит>>D/B->16-битные сегменты=0, 32-битные сегменты=1
    Иначе если для сегментов данных, то
    6 бит>>D/B->1 = используется SP (16-битный указатель стека)=0, используется ESP (32-битный указатель стека)=1
    Иначе если для нисходящих сегментов данных, то
    6 бит>>D/B->верхняя граница 64 КБ=0, верхняя граница 4 ГБ=1
    Иначе если Long Mode=1, то
    6 бит>>D/B->всегда 0

    5 бит>>Long Mode->не 64-битный код=0, 64-битный код (используется в 64-битном режиме)=1
    4 бит>>AVL->устанавливает ОС - обычно 0

    3-0>>limit_high-> старшие байты лимита
*/

#ifdef __cplusplus
extern "C" {
#endif

gdt_struct_t create_gdt_struct(uint16_t limit_low, uint32_t base, uint8_t access, uint8_t granularity);

uint8_t create_gdt_access(bool ed_r, bool w_c, bool ex, bool dt, uint8_t DPL, bool p);

uint8_t create_gdt_granularity(uint8_t limit_high, bool lm, bool db, bool g);

gdt_pointer_t create_gdt_pointer(gdt_struct_t* gdt_array, uint16_t array_size);

#ifdef __cplusplus
}
#endif

#endif