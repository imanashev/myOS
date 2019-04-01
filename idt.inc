idt_start:
   .m_baseLow     	dw   0 
   .m_selector      dw   0x8
   .m_reserved     	db   0 
   .m_flags      	db   010001110b
   .m_baseHi      	dw   0
ift_end:

idt:
    .limit	dw idt_end - idt_start - 1
	.base	dd idt_start
