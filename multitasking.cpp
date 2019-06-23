#include "multitasking.h"
#include "print.h"
#include "panic.h"

task_t tasks[TASKS_COUNT];
u8 stacks[TASKS_COUNT][TASK_STACK_SIZE];
int current_task = 0;

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

            u32 stack_end_ptr = (u32)&(stacks[i + 1]);

            auto write = [&stack_end_ptr] (u32 offset, u32 value) {
                stack_end_ptr -= offset;
                *((u32*)stack_end_ptr) = value;
            };

            write(4,   (u32)exit_handler);        // return address
            write(4,   (u32)514);                 // eflags
            write(4,   (u32)8);                   // cs
            write(4,   (u32)func);                // eip
            write(4*7, (u32)(stack_end_ptr - 4)); // esp
            
            tasks[i].esp = stack_end_ptr - 4;
            tasks[i].is_finished = 0;

            unlock();
            return;
        }
    }
    panic("Tasks limit exceeded");
}

void init_multitasking()
{
    tasks[0].is_finished = 0;
    for(int i = 1; i < TASKS_COUNT; ++i) {
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

