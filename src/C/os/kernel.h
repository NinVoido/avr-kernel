#ifndef KERNEL_H
#define KERNEL_H 

#include "avr/interrupt.h"
#include <stdint.h>

#include "config.h"
#include "task_context.h"

extern void init_kernel(void);
static void set_task(TPTR task_to_set, uint8_t task_id);

static volatile uint8_t current_task = 0;
static volatile uint8_t max_tasks = 2;
static volatile task tasks[2];

static uint16_t tick;

static __attribute__((naked)) void run_kernel(void)
{
        asm("pop __tmp_reg__");
        asm("pop __tmp_reg__");

        setup_interrupts();
        buffer = tasks[0];
        move_sp(tasks[0].sp);
        load_buffer();
        sei();
        asm("ret");
}

static inline __attribute__((always_inline)) void task_manager(void)
{
        save_buffer();
        tasks[current_task].sp = get_sp();
        ++tick;
        tasks[current_task] = buffer;
        current_task = (current_task+1) % max_tasks;
        buffer = tasks[current_task];
        move_sp(tasks[current_task].sp);
        load_buffer();
}

static inline __attribute__((always_inline)) void set_task(TPTR task_to_set, uint8_t task_id)
{

        for (uint8_t i = 0; i < 32; ++i) {
                tasks[task_id].regs[i] = 0;
        }

        tasks[task_id].pc = task_to_set;
        tasks[task_id].sreg = 0x3f;
        tasks[task_id].is_idle = 0;

        tasks[task_id].stack_bottom = RAMEND - main_stack - (task_stack * task_id);
        tasks[task_id].sp = tasks[task_id].stack_bottom;

}

#endif
