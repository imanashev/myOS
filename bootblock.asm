[BITS 16]

org 0x7c00

main:
    xor ax, ax
    mov ss, ax
    mov ds, ax
    mov es, ax
    jmp 0x0:init_cs

init_cs:
    mov ax, 0xb800
    mov es, ax
    xor bx, bx

clear_screen:
    mov ah, 0x00             ; graphics mode
    mov al, 0x03             ; text mode
    int 0x10


    mov si, string           ; load string
    mov ah, 0x0a             ; set color

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

string: 
    db 'Hello, world!',0
   ;  db '\
   ;  _     ____  _     _     ___            _       ___   ___   _     ___   __   \
   ; | |_| | |_  | |   | |   / / \  __      \ \    // / \ | |_) | |   | | \ |_/   \
   ; |_| | |_|__ |_|__ |_|__ \_\_/ /_/)      \_\/\/ \_\_/ |_| \ |_|__ |_|_/ (_)   ',0


;------------------------

times (510-($-$$)) nop

dw 0xaa55