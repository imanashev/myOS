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

void init_isr() {
    #define SET_IDT_GATE(n)     \
        extern void isr ## n(); \
        set_idt_gate(n, (u32)isr ## n);

    SET_IDT_GATE(0)
    SET_IDT_GATE(1)
    SET_IDT_GATE(2)
    SET_IDT_GATE(3)
    SET_IDT_GATE(4)
    SET_IDT_GATE(5)
    SET_IDT_GATE(6)
    SET_IDT_GATE(7)
    SET_IDT_GATE(8)
    SET_IDT_GATE(9)
    SET_IDT_GATE(10)
    SET_IDT_GATE(11)
    SET_IDT_GATE(12)
    SET_IDT_GATE(13)
    SET_IDT_GATE(14)
    SET_IDT_GATE(15)
    SET_IDT_GATE(16)
    SET_IDT_GATE(17)
    SET_IDT_GATE(18)
    SET_IDT_GATE(19)
    SET_IDT_GATE(20)
    SET_IDT_GATE(21)
    SET_IDT_GATE(22)
    SET_IDT_GATE(23)
    SET_IDT_GATE(24)
    SET_IDT_GATE(25)
    SET_IDT_GATE(26)
    SET_IDT_GATE(27)
    SET_IDT_GATE(28)
    SET_IDT_GATE(29)
    SET_IDT_GATE(30)
    SET_IDT_GATE(31)

    #undef SET_IDT_GATE
  
    set_idt(); // Load with ASM
}

void isr_handler(registers_t r) {
    Screen::print("\nRecieved interrupt: ");
    Screen::print((int)r.int_no);

    Screen::print("\nMessage: '");
    Screen::print(exception_messages[r.int_no]);

    Screen::print("'\nError code: ");
    Screen::print((int)r.err_code);
    Screen::print('\n');
}