#include "isr.h"
#include "pic8259.h"
#include "timer.h"
#include "keyboard.h"
#include "multitasking.h"
#include "tests.h"

void main()
{
    // init_isr();
    // init_pic8259();
    // enable_intr();
    // init_timer();
    // init_keyboard();
    // init_multitasking();

    testCase8();
}
