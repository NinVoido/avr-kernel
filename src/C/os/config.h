#ifndef CONFIG_H
#define CONFIG_H

#include <avr/common.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>

typedef void (*TPTR)(void);
typedef struct {
        uint8_t is_idle;
        TPTR pc;
        uint8_t sreg;
        uint8_t regs[32];
        uint16_t sp;
        uint16_t stack_bottom;
} task;

static __attribute__((naked)) void return_trap(void)
{
        asm(
                "1:" "nop" "\n\t"
                              "rjmp 1b"
                );
}

/* 
 * Hardware-specific settings
 * Currently set to work with Atmega328p
 */


#define kernel_interrupt TIMER2_COMPA_vect
#define F_CPU 8000000

#define main_stack 128
#define task_stack 64

/*
 * IMPORTANT - hardware-specific kernel preparation routine
 * Needs to turn the system timer on with a specific frequency
 * Now implemented for Atmega328p
 */

#define Prescaler 64
#define TimerDivider (F_CPU/Prescaler/1000)

inline __attribute__((always_inline)) void setup_interrupts(void)
{
        TCCR2A = 1 << WGM21;
        TCCR2B = 4 << CS20;

        TCNT2 = 0;
        OCR2A = TimerDivider & 0xFF;
        TIMSK2 = 1 << OCIE2A;
}

/* Task switching utility buffers */

static task buffer = {
        
};

static struct {
    uint8_t pc_h;
    uint8_t pc_l;
} pc_buffer;

#endif