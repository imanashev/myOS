[ORG 0x7c00]
[BITS 16]
jmp 0x0:bootblock

%include "gdt.inc"
%define SECTORS 5            ; how many sectors read from disk

clear_screen:
	pusha
    mov ah, 0x00             ; graphics mode
    mov al, 0x03             ; text mode
    int 0x10
    popa
    ret

read_disk:                   
    pusha
    mov ax, 0x7e0            ; load buffer address (0x7e0) to [es:bx]
    mov es, ax
    mov ah, 02h              ; read sector
    mov dl, 80h              ; disk number
    mov dh, 00h              ; head number
    mov ch, 00h              ; track number
    mov cl, 02h              ; sector number
    mov al, SECTORS          ; sectors count
    int 13h
    popa
    ret

install_gdt:
	pusha
    cli	
	lgdt [gdt]		          ; load GDT into GDTR
	sti
	popa
	ret

set_pe_bit:
    pusha
    cli	
	mov	eax, cr0	           ; set bit 0 in cr0--enter pmode
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
    jmp 08h:0x7e00             ; jump to protected_mode

times (510-($-$$)) nop
dw 0xaa55
