[BITS 32]
reset_segments:
    mov ax, 0x10
    mov ds, ax
    mov ss, ax
    mov es, ax

self: 
    jmp self

times (510-($-$$)) nop