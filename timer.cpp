#include "timer.h"
#include "types.h"
#include "ports.h"
#include "isr.h"
#include "print.h"

void timer_callback(registers_t regs)
{
    static int tick = 0;
    ++tick;
    if (tick % 200 == 0) {
        Screen::print("Tick: ");
        Screen::print(tick / 200);
        Screen::print("\n");
    }
}

void init_timer()
{
    register_interrupt_handler(IRQ0, timer_callback);

    // get the PIT value: hardware clock at 1193180 Hz
    u32 divisor = 1193180;

    // send the command
    send_byte_to_port(0x43, 0x36); // command port
    send_byte_to_port(0x40, low_8(divisor));
    send_byte_to_port(0x40, high_8(divisor));
}
