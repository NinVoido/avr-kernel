//#ifndef KERNEL_H
//#define KERNEL_H 

#include "config.h"

extern void init_kernel(void);
extern void run_kernel(void);
extern void task_manager(void);
extern void set_task(TPTR task_to_set);
extern void timer_service(void);
extern void set_timer_task(TPTR task_to_set, uint16_t time);

//#endif
