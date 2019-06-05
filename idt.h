#pragma once
#include "types.h"

#define IDT_ENTRIES 256

void set_idt_gate(int n, u32 handler);
void set_idt();
