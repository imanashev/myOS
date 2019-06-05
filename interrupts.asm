[extern isr_handler] ; Defined in isr.h

; Common ISR code
isr_common_stub:
    ; 1. Save CPU state
	pusha           ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax
	mov ax, ds      ; Lower 16-bits of eax = ds.
	push eax        ; save the data segment descriptor
	mov ax, 0x10    ; kernel data segment descriptor
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	
    ; 2. Call C handler
	call isr_handler
	
    ; 3. Restore state
	pop eax 
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	popa        ; Pop edi,esi,ebp,esp,ebx,edx,ecx,eax
	add esp, 8  ; Cleans up the pushed error code and pushed ISR number
	sti
	iret        ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP

%macro ISR_WITHOUT_ERRCODE 1
    [global isr%1]
    isr%1:
        cli
        push byte 0
        push byte %1
        jmp isr_common_stub
%endmacro

%macro ISR_WITH_ERRCODE 1
    [global isr%1]
    isr%1:
        cli
        push byte %1
        jmp isr_common_stub
%endmacro
	
ISR_WITHOUT_ERRCODE 0
ISR_WITHOUT_ERRCODE 1
ISR_WITHOUT_ERRCODE 2
ISR_WITHOUT_ERRCODE 3
ISR_WITHOUT_ERRCODE 4
ISR_WITHOUT_ERRCODE 5
ISR_WITHOUT_ERRCODE 6
ISR_WITHOUT_ERRCODE 7
ISR_WITH_ERRCODE    8
ISR_WITHOUT_ERRCODE 9
ISR_WITH_ERRCODE    10
ISR_WITH_ERRCODE    11
ISR_WITH_ERRCODE    12
ISR_WITH_ERRCODE    13
ISR_WITH_ERRCODE    14
ISR_WITHOUT_ERRCODE 15
ISR_WITHOUT_ERRCODE 16
ISR_WITHOUT_ERRCODE 17
ISR_WITHOUT_ERRCODE 18
ISR_WITHOUT_ERRCODE 19
ISR_WITHOUT_ERRCODE 20
ISR_WITHOUT_ERRCODE 21
ISR_WITHOUT_ERRCODE 22
ISR_WITHOUT_ERRCODE 23
ISR_WITHOUT_ERRCODE 24
ISR_WITHOUT_ERRCODE 25
ISR_WITHOUT_ERRCODE 26
ISR_WITHOUT_ERRCODE 27
ISR_WITHOUT_ERRCODE 28
ISR_WITHOUT_ERRCODE 29
ISR_WITHOUT_ERRCODE 30
ISR_WITHOUT_ERRCODE 31
ISR_WITHOUT_ERRCODE 31
