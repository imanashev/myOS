#include "ports.h"

void send_byte_to_port(u16 port, u8 data) 
{
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (data));
}

u8 read_byte_from_port(u16 port)
{
    u8 result;
    asm volatile ("inb %1, %0": "=a"(result): "dN"(port) );
    return result;
}
