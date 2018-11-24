[ORG 0x7c00]
[BITS 16]
jmp 0x0:bootblock

%include "gdt.inc"
%define SECTORS 3            ; sectors to read

clear_screen:
	pusha
    mov ah, 0x00             ; graphics mode
    mov al, 0x03             ; text mode
    int 0x10
    popa
    ret

read_disk: ;0x7e0
    pusha
    mov ax, 0x7e0            ; load buffer address to [es:bx]
    mov es, ax
    mov ah, 02h              ; чтение сектора
    mov dl, 80h              ; номер диска
    mov dh, 00h              ; номер головки  (стороны диска)
    mov ch, 00h              ; номер дорожки
    mov cl, 02h              ; номер сектора
    mov al, SECTORS          ; число секторов
    int 13h
    popa
    ret

install_gdt:
	pusha
    cli	
	lgdt [gdt]		; load GDT into GDTR
	sti
	popa			; restore registers
	ret

set_pe_bit:
    pusha
    cli	
	mov	eax, cr0	; set bit 0 in cr0--enter pmode
	or	eax, 1
	mov	cr0, eax
    popa
    ret

bootblock:
    xor ax, ax
    mov ss, ax
    mov ds, ax
    mov es, ax
    call clear_screen
    call read_disk
    call install_gdt
    call set_pe_bit
    jmp 08h:0x7e00      ;jmp to protected_mode

times (510-($-$$)) nop
dw 0xaa55
