#include "print.h"
#include "panic.h"
#include "isr.h"

#define panic(errorMsg) panic(errorMsg, __FILE__, __LINE__)

// scroll 1
void testCase1()
{
    // Screen screen;

    Screen::print("Hello, C world!\n", color::red);
    Screen::print("FooBar\n", color::green);
    Screen::scroll();
}

// scroll 2
void testCase2()
{
    // Screen screen;

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

// interrupts
void testCase4()
{
    __asm__ __volatile__("int $2");
    __asm__ __volatile__("int $3");
}

/******************************************/

void main()
{
    init_isr();

    testCase4();
}