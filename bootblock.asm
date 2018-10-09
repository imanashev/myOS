[BITS 16]
%define SECTORS 2            ; sectors to read

org 0x7c00

main:
    xor ax, ax
    mov ss, ax
    mov ds, ax
    mov es, ax
    jmp 0x0:clear_screen

clear_screen:
    mov ah, 0x00             ; graphics mode
    mov al, 0x03             ; text mode
    int 0x10

read_disk:
    xor ax, ax                 ; load buffer address to [es:bx]
    mov es, ax
    mov ax, 0x7e0
    mov es, ax
    xor bx, bx

    mov ah, 02h              ; чтение сектора
    mov dl, 80h              ; номер диска
    mov dh, 00h              ; номер головки  (стороны диска)
    mov ch, 00h              ; номер дорожки
    mov cl, 02h              ; номер сектора
    mov al, SECTORS          ; число секторов
    int 13h

    xor ax, ax               ; load videomem address
    mov ax, 0xb800
    mov es, ax
    xor bx, bx

    mov cl, 0                ; sector count
    mov di, 0x7e00           ; load buffer address
    mov si, di
    mov dh, 0x0a             ; set color

print_loop:
    mov dl, [si]             ; load symbol
    test dl, dl              ; check end of string
    jz next_sector           ; exit if 0
    mov [es:bx], dx          ; print symbol
    add bx, 2                ; next cursour position
    inc si                   ; next symbol
    jmp print_loop

next_sector:
    cmp cl, SECTORS          ; current sector number
    jge self
    add di, 512
    mov si, di               ; set next sectors address
    inc cl
    jmp print_loop

self: 
    jmp self


times (510-($-$$)) nop

dw 0xaa55
