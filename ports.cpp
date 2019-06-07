#include "ports.h"

namespace port {

void outb(u16 port, u8 data)
{
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (data));
}

u8 inb(u16 port)
{
    u8 result;
    asm volatile ("inb %1, %0": "=a"(result): "dN"(port));
    return result;
}

} // namespace port
