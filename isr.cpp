#include "isr.h"
#include "idt.h"
#include "print.h"

namespace {
const char *exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};
} // namespace

extern "C" 
{
    #define GATE(n) void isr ## n();
    #include "idt_gates.h"
    #undef GATE
}

void init_isr() 
{
    #define GATE(n) set_idt_gate(n, (u32)isr ## n);
    #include "idt_gates.h"
    #undef GATE
  
    set_idt(); // Load with ASM
}

void isr_handler(registers_t r) 
{
    Screen::print("\nRecieved interrupt: ", color::red);
    Screen::print((int)r.int_no, color::yellow);

    Screen::print("\nMessage: '", color::red);
    Screen::print(exception_messages[r.int_no], color::yellow);

    Screen::print("'\nError code: ", color::red);
    Screen::print((int)r.err_code, color::yellow);
    Screen::print("\n\n");
}
