#include "print.h"
#include "panic.h"
#include "isr.h"
#include "pic8259.h"
#include "timer.h"
#include "keyboard.h"

#define panic(errorMsg) panic(errorMsg, __FILE__, __LINE__)

// scroll 1
void testCase1()
{
    Screen::print("Hello, C world!\n", color::red);
    Screen::print("FooBar\n", color::green);
    Screen::scroll();
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
    __asm__ __volatile__("int $2");
    __asm__ __volatile__("int $3");
}

// interrupt with error code (endless loop because stack is corrupted)
void testCase5()
{
    __asm__ __volatile__("int $0xb");
}

// timer through pic8259
void testCase6()
{
    asm volatile("sti");
    init_timer();
}

// keyboard through pic8259
void testCase7()
{
    asm volatile("sti");
    init_keyboard();
}

/******************************************/

void main()
{
    init_isr();
    init_pic8259();
    testCase7();
}
