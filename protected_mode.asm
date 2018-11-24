[BITS 32]
[EXTERN main]
jmp kernel

reset_segments:
    mov ax, 0x10
    mov ds, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov es, ax
    ret

kernel:
    call reset_segments
    call main              ;go in c world
    jmp $
