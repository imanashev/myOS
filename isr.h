#pragma once
#include "types.h"

typedef struct {
   u32 ds;                                      // Data segment selector
   u32 edi, esi, ebp, esp, ebx, edx, ecx, eax;  // Pushed by pusha
   u32 int_no, err_code;                        // Interrupt number and error code
   u32 eip, cs, eflags, useresp, ss;            // Pushed by the processor automatically
} registers_t;

typedef void (*isr_t)(registers_t);

void init_isr();
extern "C" void isr_handler(registers_t r);
extern "C" void irq_handler(registers_t r);
