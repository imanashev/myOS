#include "pic8259.h"
#include "ports.h"

void init_pic8259() 
{   
    // needs icw4; cascade mode enable; edge triggered mode
    port::outb(PIC1_COMMAND, 0x11);
    port::outb(PIC2_COMMAND, 0x11);

    // offsets for interupts
    port::outb(PIC1_DATA, 0x20);
    port::outb(PIC2_DATA, 0x28);

    port::outb(PIC1_DATA, 0x04);  // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
    port::outb(PIC2_DATA, 0x02);  // ICW3: tell Slave PIC its cascade identity (0000 0010)

    // ICW4: last bit - 8086 mode
    port::outb(PIC1_DATA, 0x01);
    port::outb(PIC2_DATA, 0x01);

    // send mask to IMR (Interrupt Mask Register)
    port::outb(PIC1_DATA, 0xFF);
    port::outb(PIC2_DATA, 0xFF);
}

void enable_irq(u8 irq)
{
    u8 clear_bit = port::inb(PIC1_DATA) & ~(1 << irq);
    port::outb(PIC1_DATA, clear_bit);
}

void disable_irq(u8 irq)
{
    u8 set_bit = port::inb(PIC1_DATA) | (1 << irq);
    port::outb(PIC1_DATA, set_bit);
}
