#include "panic.h"
#include "print.h"

void panic(const char *errorMsg, const char *path, int line) 
{    
    Screen::print("\nInternal error: '", color::red);
    Screen::print(errorMsg, color::yellow);
    Screen::print("' at '", color::red);
    Screen::print(path, color::yellow);
    Screen::print("', line ", color::red);
    Screen::print(line, color::yellow);
    Screen::print("\n");
}
