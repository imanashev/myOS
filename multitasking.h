#pragma once
#include "types.h"
#include "isr.h"

#define TASKS_COUNT 10
#define TASK_STACK_SIZE 1024

typedef struct {
    u32 esp;
    bool is_finished;
} task_t; 

static inline __attribute__ ((always_inline)) void lock()
{
    asm volatile ("pushf");
    asm volatile ("cli");
}

static inline __attribute__ ((always_inline)) void unlock()
{
    asm volatile ("popf");
}

void add_task(u32 func);
void switch_task(task_stack_t &stack);
bool is_current_task_finished();

void init_multitasking();
