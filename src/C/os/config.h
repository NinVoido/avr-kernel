#ifndef CONFIG_H
#define CONFIG_H

#include <avr/common.h>
#include <avr/interrupt.h>

typedef void (*TPTR)(void);

/* Software kernel configuration */
#define task_queue_size 20
#define main_timer_queue_size 15

/* 
 * Kernel idle routine
 * Does nothing by default
 * To change its behaviour, see config.c
 */
extern void idle_task(void);

/* 
 * Hardware-specific settings
 * Currently set to work with Atmega328p
 */
#define int_enable sei()
#define int_disable cli()
#define int_flag SREG_I
#define status_reg SREG
#define kernel_interrupt TIMER2_COMPA_vect
#define F_CPU 8000000

/*
 * IMPORTANT - hardware-specific kernel preparation routine
 * Needs to turn the system timer on with a specific frequency
 * Now implemented for Atmega328p
 */

extern void kernel_preparation(void);

#endif
