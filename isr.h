#pragma once
#include "types.h"

#define IRQ0 32 // timer
#define IRQ1 33 // keyboard

typedef struct {
   u32 ds;                                      // Data segment selector
   u32 edi, esi, ebp, esp, ebx, edx, ecx, eax;  // Pushed by pushad
   u32 int_no, err_code;                        // Interrupt number and error code
   u32 eip, cs, eflags, useresp, ss;            // Pushed by the processor automatically
} registers_t;

typedef struct {
   u32 esp;                                           // Pushed esp singly, because popad doesn't restore it
   u32 edi, esi, ebp, esp_dupl, ebx, edx, ecx, eax;   // Pushed by pushad
   u32 eip, cs, eflags, useresp, ss;                  // Pushed by the processor automatically
} task_stack_t;

typedef void (*isr_t)(registers_t);

extern "C" void isr_handler(registers_t r);
extern "C" void irq_handler(registers_t r);
extern "C" void irq_timer_handler();

static inline __attribute__ ((always_inline)) void enable_intr()
{
    asm volatile("sti");
}

static inline __attribute__ ((always_inline)) void disable_intr()
{
    asm volatile("cli");
}

void init_isr();
void register_interrupt_handler(u8 n, isr_t handler);
