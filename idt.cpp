#include "idt.h"

namespace {
#define KERNEL_CS 0x08

typedef struct {
    u16 low_offset; // Lower 0..15 bits of handler function address
    u16 sel;        // Kernel segment selector
    u8 zero;        // Unused, always 0
    /* First byte
     * Bit 7: "Interrupt is present"
     * Bits 6-5: Privilege level of caller (0=kernel..3=user)
     * Bit 4: Set to 0 for interrupt gates
     * Bits 3-0: bits 1110 = decimal 14 = "32 bit interrupt gate" */
    u8 flags; 
    u16 high_offset; // Higher 16..31 bits of handler function address
} __attribute__((packed)) idt_gate_t ;

typedef struct {
    u16 limit;
    u32 base;
} __attribute__((packed)) idt_register_t;

idt_gate_t idt[IDT_ENTRIES];
idt_register_t idt_reg;

} // namespace

void set_idt_gate(int n, u32 handler) 
{
    idt[n].low_offset = low_16(handler);
    idt[n].sel = KERNEL_CS;
    idt[n].zero = 0;
    idt[n].flags = 0x8E; 
    idt[n].high_offset = high_16(handler);
}

void set_idt() 
{
    idt_reg.base = (u32) &idt;
    idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1;
    __asm__ __volatile__("lidt (%0)" : : "r" (&idt_reg));
}
