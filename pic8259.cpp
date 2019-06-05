#include "pic8259.h"
#include "ports.h"

// PIC1 - master
// PIC2 - slave
#define PIC1_COMMAND    0x20
#define PIC1_DATA       0x21
#define PIC2_COMMAND    0xA0
#define PIC2_DATA       0xA1

void init_pic8259() 
{   
    // needs icw4; cascade mode enable; edge triggered mode
    send_byte_to_port(PIC1_COMMAND, 0x11);
    send_byte_to_port(PIC2_COMMAND, 0x11);

    // offsets for interupts
    send_byte_to_port(PIC1_DATA, 0x20);  
    send_byte_to_port(PIC2_DATA, 0x28);

    send_byte_to_port(PIC1_DATA, 0x04);  // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
    send_byte_to_port(PIC2_DATA, 0x02);  // ICW3: tell Slave PIC its cascade identity (0000 0010)

    // ICW4: last bit - 8086 mode
    send_byte_to_port(PIC1_DATA, 0x01);
    send_byte_to_port(PIC2_DATA, 0x01);

    // send mask to IMR (Interrupt Mask Register)
    send_byte_to_port(PIC1_DATA, 0x0);
    send_byte_to_port(PIC2_DATA, 0x0);
}
