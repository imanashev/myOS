#pragma once
#include "types.h"

// PIC1 - master
// PIC2 - slave
#define PIC1_COMMAND    0x20
#define PIC1_DATA       0x21
#define PIC2_COMMAND    0xA0
#define PIC2_DATA       0xA1

void enable_irq(u8 irq);
void disable_irq(u8 irq);

void init_pic8259();
