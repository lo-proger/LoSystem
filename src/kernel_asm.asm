[BITS 16]
global _start

extern kernel_main

section .text
_start: ; init_32_mode
    ; Переход в 32 битный режим
    mov si, msg_loaded
    call print_string

    cli
    lgdt [gdt32_pointer]
    
    ; Установка бита PE
    mov eax, cr0
    or eax, 1
    mov cr0, eax

    jmp 0x08:init_64_mode

print_string:
    mov ah, 0x0E
.loop:
    lodsb
    test al, al
    jz .done
    int 0x10
    jmp .loop
.done:
    ret

section .data
msg_loaded: db "Kernel loaded", 13, 10, 0

; gdt для защищеного режима

gdt32_start:
gdt32_null_32:
    dq 0x0000000000000000
gdt32_code:
    dw 0xFFFF
    dw 0x0000
    db 0x00
    db 0b10011010 ; Present=1, DPL=00, Type=1, Executable=1, Readable=1, Accessed=0
    db 0b11001111 ; AVL=0, Long=0, D/B=1, G=1, limit_high=1111
    db 0x00
gdt32_data:
    dw 0xFFFF
    dw 0x0000
    db 0x00
    db 0b10010010 ; Present=1, DPL=00, Type=1, Executable=0, Writable=1, Direction=0, Accessed=0
    db 0b11001111 ; AVL=0, Long=0, D/B=1, G=1, limit_high=1111
    db 0x00
gdt32_end:

gdt32_pointer:
    dw gdt32_end - gdt32_start - 1
    dd gdt32_start


; gdt для длинного режима

gdt64_start:
gdt64_null_32:
    dq 0x0000000000000000
gdt64_code:
    dw 0xFFFF
    dw 0x0000
    db 0x00
    db 0b10011010 ; Present=1, DPL=00, Type=1, Executable=1, Readable=1, Accessed=0
    db 0b10101111 ; AVL=0, Long=1, D/B=0, G=1, limit_high=1111
    db 0x00
gdt64_data:
    dw 0xFFFF
    dw 0x0000
    db 0x00
    db 0b10010010 ; Present=1, DPL=00, Type=1, Executable=0, Writable=1, Direction=0, Accessed=0
    db 0b11001111 ; AVL=0, Long=0, D/B=1, G=1, limit_high=1111
    db 0x00
gdt64_end:

gdt64_pointer:
    dw gdt64_end - gdt64_start - 1
    dd gdt64_start


;    gdt_struct:
;       limit_low ; указывает сколько памяти начиная с base может использовать процесс (16 бит)
;       base_low ; указывает адрес в памяти (16 бит)
;       base_middle ; продолжение base_low (8 бит)
;       access ; флаги p, dpl, s, type, (e, w) - type->3 = 0, (c, r) - type->3 = 1 (8 бит)
;       granularity ; limit, флаги l, avl, d/b, g (8 бит)
;       base_high; ; продолжение base_middle (8 бит)
;
;
;    От старшего к младшему, т.е. в 0b100000000 - 1 это 7 бит(старший), а в 0b000000001 - 1 это 0 бит(младший)
;
;    gdt_struct::access -
;    7 бит>>present->сегмент отсутствует в памяти=0, присутствует=1
;    6-5 бит>>DPL(ring)->максимальные привилегии=00,ring 1=01, ring 2=10, минимальные привилегии=11
;    4 бит>>descriptor type->системный сегмент=0, обычный=1
;    3 бит>>executable->не исполняемый=0, исполняемый=1

;    Если 3 бит = 0, то
;    2 бит>>expansion direction->cегмент растёт вверх (обычные данные)=0, cегмент растёт вниз (стек)=1
;    1 бит>>writable->чтение=0, чтение и запись=1
;    Иначе
;    2 бит>>сonforming->выполнение только с того же уровня ring=0, выполнение с других уровней ring=1
;    1 бит>>readable->только выполнение=0, можно читать=1
;
;    0 бит>>accessed - cpu устанавливает
;
;    gdt_struct::granularity -
;    7 бит>>granularity->лимит измеряется в байтах (1 байт)=0, лимит измеряется в страницах по 4КБ (4096 байт)=1
;    Если для сегментов кода, то
;    6 бит>>D/B->16-битные сегменты=0, 32-битные сегменты=1
;    Иначе если для сегментов данных, то
;    6 бит>>D/B->1 = используется SP (16-битный указатель стека)=0, используется ESP (32-битный указатель стека)=1
;    Иначе если для нисходящих сегментов данных, то
;    6 бит>>D/B->верхняя граница 64 КБ=0, верхняя граница 4 ГБ=1
;    Иначе если Long Mode=1, то
;    6 бит>>D/B->всегда 0

;    5 бит>>Long Mode->не 64-битный код=0, 64-битный код (используется в 64-битном режиме)=1
;    4 бит>>AVL->устанавливает ОС - обычно 0
;
;    3-0>>limit_high-> старшие байты лимита


[BITS 32]
section .text
init_64_mode:
    ; настройка регистров памяти по gdt32_data
    mov ax, 0x10 ; 0x10 - gdt32_data
    mov ds, ax
    mov es, ax 
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0x7C00 ; начало стека

    cli

    ; Переход в 64 битный режим 
    
    lgdt [gdt64_pointer]

    call init_paging

    ; Устанавливаем бит PAE 
    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax

    ; Загружаем адресс таблицы
    mov eax, PML4_ADDR
    mov cr3, eax

    mov ecx, 0xC0000080 ; Номер MSR для EFER
    rdmsr               ; Читаем текущее значение
    or eax, 1 << 8      ; Устанавливаем бит LME (Long Mode Enable)
    wrmsr               ; Записываем обратно

    mov eax, cr0
    or eax, 1 << 31     ; Устанавливаем бит PG (Paging)
    mov cr0, eax

    jmp 0x08:kernel_jmp

section .data
PAGE_PRESENT  equ 0x001
PAGE_RW       equ 0x002
PAGE_USER     equ 0x004
PAGE_PWT      equ 0x008
PAGE_CACHE    equ 0x010
PAGE_ACCESSED equ 0x020
PAGE_DIRTY    equ 0x040
PAGE_SIZE_BIG equ 0x080
PAGE_GLOBAL   equ 0x100
PAGE_NX       equ 0x8000000000000000


;   page_table_entry:
;       flags ; флаги и служебные биты (12 бит)
;       address ; физический адрес страницы или следующей таблицы (40 бит)
;       AVL ; доступно ОС (11 бит)
;       NX ; No Execute — запрет на выполнение кода (1 бит)
;
;   От старшего к младшему, т.е. в 0b100000000 - 1 это 7 бит (старший), а в 0b000000001 - 1 это 0 бит (младший)
;
;   63 бит>>NX->выполнение разрешено=0, запрещено=1
;
;   page_table_entry::flags —
;   8 бит>>Global->обычная страница=0, глобальная=1
;   7 бит>>Page Size->только в PD/PDPT, обычная страница (4 КБ)=0, большая (2 МБ для PD или 1 ГБ для PDPT)=1
;   6 бит>>Dirty->устанавлевается CPU, не изменялась=0, была запись в страницу=1
;   5 бит>>Accessed->устанавлевается CPU, не использовалась=0, была операция чтения/записи=1
;   4 бит>>Cache Disable->кэширование разрешено=0, отключить кэш=1
;   3 бит>>Write-Through->обычное кэширование=0, сквозная запись=1
;   2 бит>>User/Supervisor->доступ только из ядра=0 (Ring 0-2), доступен пользователю=1 (Ring 3)
;   1 бит>>Read/Write->только чтение=0, чтение и запись=1
;   0 бит>>Present->страница отсутствует=0, страница присутствует=1

PAGE_SIZE equ 0x1000
PML4_ADDR equ 0x00010000
PDPT_ADDR equ PML4_ADDR + PAGE_SIZE
PD_ADDR equ PDPT_ADDR + PAGE_SIZE

section .text
init_paging:
    push eax
    push ebx
    push ecx
    push edi
    
    ; Cоздание таблиц страниц для длинного режима

    ; Очищаем PML4 таблицу (4096 байт)
    mov edi, PML4_ADDR
    mov ecx, 1024        ; 4096 байт / 4 байта = 1024 двойных слова
    xor eax, eax
    rep stosd
    
    ; Очищаем PDPT таблицу
    mov edi, PDPT_ADDR
    mov ecx, 1024
    xor eax, eax
    rep stosd
    
    ; Очищаем PD таблицу
    mov edi, PD_ADDR
    mov ecx, 1024
    xor eax, eax
    rep stosd
    
    ; Cоздаем отображение страниц (identity mapping) для первых 2МБ памяти
    
    ; PML4[0] -> PDPT
    mov eax, PDPT_ADDR
    or eax, PAGE_PRESENT | PAGE_RW
    mov [PML4_ADDR], eax
    
    ; PDPT[0] -> PD
    mov eax, PD_ADDR
    or eax, PAGE_PRESENT | PAGE_RW
    mov [PDPT_ADDR], eax
    
    ; PD[0] -> 2MB страница (физический адрес 0x00000000)
    mov eax, 0x00000000
    or eax, PAGE_PRESENT | PAGE_RW | PAGE_SIZE_BIG
    mov [PD_ADDR], eax
    
    ; Восстанавливаем регистры
    pop edi
    pop ecx
    pop ebx
    pop eax
    ret


[BITS 64]
section .text 
kernel_jmp:
    ; настройка регистров памяти по gdt64_data
    mov ax, 0x10 ; 0x10 - gdt64_data
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov rsp, 0x7FFFF ; начало стек

    call kernel_main
    
    ; Бесконечный цикл на случай возврата
    jmp $