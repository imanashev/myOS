[BITS 32]
[EXTERN main]
jmp kernel

init_segments:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret

kernel:
    call init_segments
    call main                  ; go in c world
    jmp $
