#pragma once
#include "isr.h"

#define TICKS_FOR_PRINT -1
#define TICKS_FOR_TASK 1000

void init_timer();
extern "C" void timer_callback(task_stack_t stack);
