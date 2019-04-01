#include "panic.h"
#include "print.h"

void panic(const char *errorMsg, const char *path, int line) 
{
    Screen screen;
    
    screen.print("\nInternal error: '", color::red);
    screen.print(errorMsg, color::yellow);
    screen.print("' at '", color::red);
    screen.print(path, color::yellow);
    screen.print("', line ", color::red);
    screen.print(line, color::yellow);
    screen.print("\n");
}
