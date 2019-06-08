#include "multitasking.h"
#include "print.h"
#include "panic.h"

task_t tasks[TASKS_COUNT];
u8 stacks[TASKS_COUNT][TASK_STACK_SIZE];
int current_task = -1;

bool is_task_finished(int n) 
{
    return tasks[n].is_finished;
}

bool is_current_task_finished()
{
    return is_task_finished(current_task);
}

void exit_handler() {
    #ifdef DEBUG
    Screen::print("exit process with pid=");
    Screen::print(current_task);
    Screen::print("\n");
    #endif

    tasks[current_task].is_finished = 1;
    disable_intr();
    irq_timer_handler();
}

void write(u32 &stack_ptr, u32 value, u32 offset)
{
    stack_ptr -= offset;
    *((u32*)stack_ptr) = value;
}

void add_task(u32 func) 
{
    for(int i = 0; i < TASKS_COUNT; ++i) {
        if(is_task_finished(i)) {
            lock();

            #ifdef DEBUG
            Screen::print("Add process with pid=");
            Screen::print(i);
            Screen::print("\n");
            #endif

            tasks[i].is_finished = 0;

            u32 stack_ptr = (u32)&(stacks[i + 1]);

            write(stack_ptr, (u32)exit_handler,  4);   // return address
            write(stack_ptr, (u32)514,           4);   // eflags
            write(stack_ptr, (u32)8,             4);   // cs
            write(stack_ptr, (u32)func,          4);   // eip
            write(stack_ptr, (u32)(stack_ptr - 4), 4*7);
            
            tasks[i].esp = stack_ptr - 4;

            unlock();
            return;
        }
    }
    panic("Tasks limit exceeded");
}

void init_multitasking()
{
    for(int i = 0; i < TASKS_COUNT; ++i) {
        tasks[i].is_finished = 1;
    }
}

void switch_task(task_stack_t &stack)
{
    tasks[current_task].esp = stack.esp;

    auto switch_focus = [&] (int i) {
        stack.esp = tasks[i].esp;
        current_task = i;

        #ifdef DEBUG
        Screen::print("switch focus to process with pid=");
        Screen::print(current_task);
        Screen::print("\n");
        #endif
    };
    
    for (int i = current_task + 1; i < TASKS_COUNT; ++i) {
        if (!is_task_finished(i)) {
            switch_focus(i);
            return;
        }
    }
    for (int i = 0; i <= current_task; i++) {
        if (!is_task_finished(i)) {
            switch_focus(i);
            return;
        }
    }

    #ifdef DEBUG
    Screen::print("Empty task queue\n", color::red);
    #endif
}

