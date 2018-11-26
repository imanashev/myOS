[BITS 16]

gdt_start:
; null descriptor 
    dd 0
    dd 0

; code descriptor:
    dw 0FFFFh            ; limit low
    dw 0                 ; base low
    db 0                 ; base middle
    db 10011010b         ; access
    db 11001111b         ; granularity
    db 0                 ; base high

; data descriptor:
    dw 0FFFFh            ; limit low (Same as code)
    dw 0                 ; base low
    db 0                 ; base middle
    db 10010010b         ; access
    db 11001111b         ; granularity
    db 0                 ; base high
gdt_end:

gdt: 
    dw gdt_end - gdt_start - 1    ; limit (Size of GDT)
    dd gdt_start                  ; base of GDT
