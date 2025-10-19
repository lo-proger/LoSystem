[BITS 16]
[ORG 0x7C00]

start:
    ; Инициализация
    xor ax, ax
    mov ds, ax ;обнуление регистра Data Segment
    mov es, ax ;обнуление регистра Extra Segment
    mov ss, ax ;установка начала стека на адрес 0x0000
    mov sp, 0x7C00 ;установка конца стека на адрес 0x7C00

    mov [boot_drive], dl ;сохраняем номер диска

    mov si, msg_loaded
    call print_string

    mov si, kernel_read
    mov dl, [boot_drive]
    mov ah, 0x42 ;указывает что надо использовать lba, а не chs
    int 0x13 ;прерывание BIOS для работы с диском
    jc disk_error

    jmp 0x0000:0x1000 ;переходим на ядро

disk_error:
    mov si, msg_disk_error
    call print_string

    mov al, ah 
    call print_hex

    jmp $ ;бесконечный цикл


print_hex:
    mov bl, al ;сохраняем al
    
    ; Выводим "0x"
    mov si, hex_prefix
    call print_string
    
    ; Верхняя тетрада
    mov al, bl
    mov cl, 4
    shr al, cl 
    call .print_digit
    
    ; Нижняя тетрада  
    mov al, bl
    and al, 0x0F
    call .print_digit

    ret
    
.print_digit:
    cmp al, 9
    jbe .digit
    add al, 7
.digit:
    add al, 0x30
    mov ah, 0x0E
    int 0x10
    ret


;Функция печати текста
print_string:
    mov ah, 0x0E ;указывает на функцию телетайпного вывода символа (по простому - печатает один символ на экран)
.loop:
    lodsb ;загружает байт из памяти по адресу ds:si в регистр al и автоматически увеличивает si (не знаю почему она так называется)
    test al, al
    jz .done
    int 0x10 ;прерывание BIOS для вывода символа
    jmp .loop
.done:
    ret


;Область данных
msg_loaded: db "Boot loaded", 13, 10, 0
msg_disk_error: db "Disk error: ", 0
boot_drive: db 0
hex_prefix: db "0x", 0

kernel_read: ;DAPS
    db 0x10 ;размер пакета (16 байт)
    db 0
    dw 2 ;врядли вывод строки kernel loaded будет веслить больше 1кб так что с запасиком
    dw 0x1000 ;через [org 0x1000] укажем в коде ядра
    dw 0x0000
    dq 1 ;отсчет с 0, а первые 512 байт занимает загрузчик

times 510 - ($ - $$) db 0 ;заполняет остаток файла до 512 байт нулями (не знаю почему такая странная формула вычисления, но работает)
dw 0xAA55 ; Сигнатура загрузочного сектора (чтоб BIOS нашел)