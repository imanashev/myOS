#include "timer.h"
#include "types.h"
#include "ports.h"
#include "isr.h"
#include "print.h"

int tick = 0;

static void Tick()
{
    // Todo: fix print string method
    Screen::print('T');
    Screen::print('i');
    Screen::print('c');
    Screen::print('k');
    Screen::print(':');
    Screen::print(' ');
    Screen::print(tick / 100);
    Screen::newLine();
}

static void timer_callback(registers_t regs)
{
    ++tick;
    if (tick % 100 == 0) {
        Tick();
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