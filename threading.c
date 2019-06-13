#include "threading.h"

#include "kmalloc.h"
#include "interrupt.h"

#define MAX_NUM_THREADS 14      // Set by number of PTL4 entries reserved for kernel stacks

struct KThread current_thread;
struct KThread next_thread;

struct KThread {
    int stack_num;
    kproc_t entry_point;
    void *args;
};

struct KThread *threads[MAX_NUM_THREADS + 1] = {0};    // Ignore index 0

extern "C" void sys_call_isr_wrapper(void);
void init_threading() {
    register_isr(sys_call_isr_wrapper, 0x80);
}

void PROC_create_kthread(kproc_t entry_point, void *args) {
    int stack_number;
    for (stack_number = 1; stack_number <= MAX_NUM_THREADS; stack_number++) {
        if (!threads[stack_number])
            break;
    }
    struct KThread *thread = (struct KThread *)kmalloc(sizeof(*thread));
    threads[stack_number] = thread;
    thread->stack_num = stack_number;
    thread->entry_point = entry_point;
    thread->args = args;
}

void PROC_reschedule();

void PROC_run() {
    if (current_thread)
        yield();
    else
        PROC_reschedule();
}

void kexit();

extern "C" void sys_call_interrupt_handler() {
    switch (current_thread.
    current_thread.entry_point(args);
}