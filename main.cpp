#include "print.h"
#include "panic.h"

#define panic(errorMsg) panic(errorMsg, __FILE__, __LINE__)

// scroll 1
void testCase1()
{
    Screen screen;

    screen.print("Hello, C world!\n", color::red);
    screen.print("FooBar\n", color::green);
    screen.scroll();
}

// scroll 2
void testCase2()
{
    Screen screen;

    char string[] = ":\tHello, C world!\n";
    int i = 1;
    while(i <= 20) {
        screen.print(i);
        screen.print(string, i % 15 + 1);
        ++i;
    }
    int j = 0;
    while(true) {
        if(j % 10000000 == 0) {
            screen.print(i);
            screen.print(string, i % 15 + 1);
            ++i;
        }
        ++j;
    }
}

// tabs
void testCase3()
{
    Screen screen;

    screen.print("12341234123412341234123412341234123412341234123412341234123412341234123412341234\n");
    screen.print("\ttab\n");
    screen.print("1\ttab\n");
    screen.print("12\ttab\n");
    screen.print("123\ttab\n");
    screen.print("1234\ttab\n");
    screen.print("23456789abcdefghijklmnopqrstuvwxyz123456789123456789abcdefghijklmnopqrstuvwxyz\t12");
}

/******************************************/

void main()
{
    testCase1();
    panic("Big mistake!");
}