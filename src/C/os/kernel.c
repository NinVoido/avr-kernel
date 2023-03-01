/* To be compiled using AVR-GCC 12.2.0 with avr-libc under GNU/Linux */

/* avr-libc includes */
#include <avr/interrupt.h>
#include <inttypes.h>
/* local config */
#include "config.h"
#include "kernel.h"

volatile static TPTR task_queue[task_queue_size + 1];

volatile static struct {
        TPTR task;
        uint16_t time;
} main_timer[main_timer_queue_size + 1];

inline void init_kernel(void) {
        uint8_t i;
        
        /* initialize task queue with idle tasks */
        for (i = 0; i != task_queue_size + 1; ++i) {
                task_queue[i] = idle_task;
        }
        /* initialize timer queue with idle tasks */
        for (i = 0; i != main_timer_queue_size + 1; ++i) {
                main_timer[i].task = idle_task;
                main_timer[i].time = 0;
        }
}

inline void run_kernel(void) {
        kernel_preparation();
        
        int_enable;
}

inline void task_manager(void)
{
        uint8_t i = 0;
        TPTR go_to_task = idle_task;

        int_disable;

        go_to_task = task_queue[0];

        if (go_to_task == idle_task) {
                int_enable;
                (idle_task) ();
        } else {
                for (i = 0; i < task_queue_size; ++i)
                        task_queue[i] = task_queue[i + 1];

                task_queue[task_queue_size] = idle_task;
                int_enable;
                (go_to_task) ();
        }
}

void set_task(TPTR task_to_set)
{
        uint8_t i = 0;
        uint8_t interrupts_disabled = 0;

        if (status_reg & (1 << int_flag)) {
                int_disable;
                interrupts_disabled = 1;
        }

        while (task_queue[i] != idle_task) {
                i++;
                if (i == task_queue_size+1)
                        goto check_interrupts;
        }

        task_queue[i] = task_to_set;

check_interrupts:
        if (interrupts_disabled)
                int_enable;
}

/*
 * Function to be executed on timer interrupt
 * Decrements timers of all tasks and **tries** to push the needed
 * tasks into the main task queue.
 * IMPORTANT: if the task queue is already full, task will just dissapear
 * with no trace.
 * TODO - change the dissapearing task behaviour (performance-critical?)
 */
inline void timer_service(void)
{
        uint8_t i;

        for (i = 0; i != main_timer_queue_size + 1; ++i) {
                
                if (main_timer[i].task == idle_task)
                        continue;

                if (main_timer[i].time != 1) {
                        main_timer[i].time--;
                } else {
                        set_task(main_timer[i].task);
                        main_timer[i].task = idle_task;
                }
        }
}

/*
 * Function to manipulate timer queue.
 * If task_to_set is already in the queue, its time will be changed to new_time.
 * If task_to_set is not in the queue, it will be appended to it with time of
 * new_time.
 * TODO - split this into retime() and new_timer_task() ?
 */
void set_timer_task(TPTR task_to_set, uint16_t new_time)
{
        uint8_t i;
        uint8_t interrupts_disabled = 0;

        if (status_reg & (1 << int_flag)) {
                int_disable;
                interrupts_disabled = 1;
        }

        for (i = 0; i != main_timer_queue_size + 1; ++i) {
                if (main_timer[i].task == task_to_set) {
                        main_timer[i].time = new_time;
                        goto check_interrupts;
                }
        }

        for (i = 0; i != main_timer_queue_size; ++i) {
                if (main_timer[i].task == idle_task) {
                        main_timer[i].task = task_to_set;
                        main_timer[i].time = new_time;
                        goto check_interrupts;
                }
        }

check_interrupts:
         if (interrupts_disabled)
                 int_enable;
}
