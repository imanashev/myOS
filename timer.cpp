#include "timer.h"
#include "types.h"
#include "ports.h"
#include "print.h"
#include "multitasking.h"
#include "pic8259.h"

#define IS_TIME_FOR(n) (tick % n == 0)

void timer_callback(task_stack_t stack)
{
    static u32 tick = 1;

    if (IS_TIME_FOR(TICKS_FOR_PRINT)) {
        #ifdef DEBUG
        Screen::print("Tick!\n", color::yellow);
        #endif
    }

    // multitasking
    if (IS_TIME_FOR(TICKS_FOR_TASK) || is_current_task_finished()) {
        switch_task(stack);
    }

    ++tick;
    port::outb(PIC1_COMMAND, 0x20); // send EOI
}

void init_timer()
{
    // get the PIT value: hardware clock at 1193180 Hz
    u32 divisor = 1193180;

    // send the command
    port::outb(0x43, 0x36); // command port
    port::outb(0x40, low_8(divisor));
    port::outb(0x40, high_8(divisor));

    enable_irq(IRQ0);
}
