#include "time.h"

void sleep(u32 ms)
{
    while (ms--) {
        for (u16 i = 1; i; ++i);
    }
}