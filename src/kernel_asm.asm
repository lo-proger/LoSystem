[BITS 16]
global _start

extern kernel_main

_start:
    mov si, msg_loaded
    call print_string

    cli
    lgdt [gdt_pointer]
    
    ; Установка бита PE
    mov eax, cr0
    or eax, 1
    mov cr0, eax

    jmp 0x08:kernel_jmp

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

msg_loaded: db "Kernel loaded", 13, 10, 0

gdt_start:
gdt_null:
    dq 0x0000000000000000
gdt_code:
    dw 0xFFFF
    dw 0x0000
    db 0x00
    db 0b10011010 ; Present=1, DPL=00, Type=1, Executable=1, Readable=1, Accessed=0
    db 0b11001111 ; AVL=0, Long=0, D/B=1, G=1, limit_high=1111
    db 0x00
gdt_data:
    dw 0xFFFF
    dw 0x0000
    db 0x00
    db 0b10010010 ; Present=1, DPL=00, Type=1, Executable=0, Writable=1, Direction=0, Accessed=0
    db 0b11001111 ; AVL=0, Long=0, D/B=1, G=1, limit_high=1111
    db 0x00
gdt_end:

gdt_pointer:
    dw gdt_end - gdt_start - 1
    dd gdt_start

[BITS 32]
kernel_jmp:
    mov ax, 0x10
    mov ds, ax
    mov es, ax 
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0x90000  

    call kernel_main

