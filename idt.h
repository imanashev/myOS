#pragma once
#include "types.h"

void set_idt_gate(int n, u32 handler);
void set_idt();
