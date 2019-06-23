#include "tests.h"
#include "panic.h"
#include "print.h"
#include "isr.h"
#include "pic8259.h"
#include "timer.h"
#include "keyboard.h"
#include "multitasking.h"
#include "time.h"

// panic
void testCase1()
{
    panic("This is panic test");
}

// scroll 2
void testCase2()
{
    char string[] = ":\tHello, C world!\n";
    int i = 1;
    while(i <= 20) {
        Screen::print(i);
        Screen::print(string, i % 15 + 1);
        ++i;
    }
    int j = 0;
    while(true) {
        if(j % 10000000 == 0) {
            Screen::print(i);
            Screen::print(":\tHmmmm\n", i % 15 + 1);
            Screen::print(i);
            Screen::print(string, i % 15 + 1);
            ++i;
        }
        ++j;
    }
}

// tabs
void testCase3()
{
    Screen::print("12341234123412341234123412341234123412341234123412341234123412341234123412341234\n");
    Screen::print("\ttab\n");
    Screen::print("1\ttab\n");
    Screen::print("12\ttab\n");
    Screen::print("123\ttab\n");
    Screen::print("1234\ttab\n");
    Screen::print("23456789abcdefghijklmnopqrstuvwxyz123456789123456789abcdefghijklmnopqrstuvwxyz\t12");
}

// interrupts without error code
void testCase4()
{
    init_isr();

    asm volatile ("int $2");
    asm volatile ("int $3");
}

// interrupt with error code (endless loop because stack is corrupted)
void testCase5()
{
    init_isr();

    asm volatile ("int $0xb");
}

// timer through pic8259 (works only in debug mode. Don't forget to change TICKS_FOR_PRINT in timer.h)
void testCase6()
{
    init_isr();
    init_pic8259();
    enable_intr();
    init_multitasking(); 

    init_timer();
}

// keyboard through pic8259
void testCase7()
{
    init_isr();
    init_pic8259();
    enable_intr();
    
    init_keyboard();
}

void main_task();
void task1();
void task2();
void task3();
void task4();

// multitasking
void testCase8()
{
    init_isr();
    init_pic8259();
    enable_intr();
    init_timer();
    init_keyboard();

    init_multitasking();
    add_task((u32) task1);
    add_task((u32) task2);

    main_task();
}

/* Tasks for multitasking testCase8 */
/************************************/

#define PRINT_DELAY 70

void main_task()
{
    int i = 0;
    while(1) {
        Screen::print("Main task: ", color::brown);
        Screen::print(i++, color::brown);
        Screen::print("\n");

        sleep(PRINT_DELAY);
    }
}

void task1()
{
    int i = 0;
    while(1) {
        Screen::print("Task1 tick: ", color::magenta);
        Screen::print(i++, color::magenta);
        Screen::print("\n");

        // add_task((u32)task1);

        sleep(PRINT_DELAY);
    }
}

void task2()
{
    int i = 0;
    Screen::print("Task2 tick: ", color::light_green);
    Screen::print(i++, color::light_green);
    Screen::print("\n");

    add_task((u32)task3);
}

void task3()
{
    int i = 0;
    while(1) {
        Screen::print("Task3 tick: ", color::light_blue);
        Screen::print(i++, color::light_blue);
        Screen::print("\n");

        if (i % 3 == 0) {
            add_task((u32)task4);
        }

        sleep(PRINT_DELAY);
    }
}

void task4()
{
    int i = 0;

    Screen::print("Task4 tick: ", color::light_red);
    Screen::print(i++, color::light_red);
    Screen::print("\n");
    
    // add_task((u32)task4);

    sleep(PRINT_DELAY);
}
