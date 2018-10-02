[BITS 16]

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
    xor ax, ax				 ; load buffer address
    mov es, ax
    mov ax, 0x7e0
    mov es, ax
    xor bx, bx

    mov ah, 02h              ; чтение сектора
    mov dl, 80h              ; номер диска
    mov dh, 00h              ; номер головки  (стороны диска)
	mov ch, 00h              ; номер дорожки
    mov cl, 02h              ; номер сектора
    mov al, 01h              ; число секторов
    int 13h

    xor ax, ax				 ; load videomem address
    mov es, ax
    mov ax, 0xb800
    mov es, ax
    xor bx, bx

    mov si, 0x7e00			 ; load buffer address
    mov ah, 0x0a			 ; set color

print_loop:
    mov al, [si]             ; load symbol
    test al, al              ; check end of string
    jz self                  ; exit if 0
    mov [es:bx], ax          ; print symbol
    add bx, 2                ; next cursour position
    inc si                   ; next symbol
    jmp print_loop



self: 
    jmp self

;------------------------

; string: 
;     db 'Hello, world!',0

;------------------------

times (510-($-$$)) nop

dw 0xaa55