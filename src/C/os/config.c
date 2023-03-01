#include <avr/io.h>
#include "config.h"

void idle_task(void)
{
        /* Do something */
}

#define Prescaler 64
#define TimerDivider (F_CPU/Prescaler/1000)

void kernel_preparation(void)
{
        TCCR2A = 1 << WGM21;
        TCCR2B = 4 << CS20;

        TCNT2 = 0;
        OCR2A = TimerDivider & 0xFF;
        TIMSK2 = 1 << OCIE2A;
}
