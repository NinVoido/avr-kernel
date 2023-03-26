#include <avr/io.h>
#include <avr/wdt.h>

#include "./os/kernel.h"
#include "./os/config.h"
#include "./os/task_context.h"

ISR(kernel_interrupt, ISR_NAKED)
{
//        save_buffer();
//        tick++;
//        if (tick == 1000) {
//                PORTB ^= 1<<5;
//        }
//
//        if (tick == 2000) {
//                PORTB &= ~(1<<5);
//                tick = 0;
//        }
//        load_buffer();
        task_manager();
        asm("reti");
}

void led_off(void);
void led_on(void);

void led_on(void)
{
        while(1) {
                if (tick == 1000 | tick == 1001) {
                        PORTB = 1<<5;
                }
        }
}

void led_off(void)
{
        while (1) {
                if (tick == 2000 | tick == 2001) {
                        tick = 0;
                        PORTB &= ~(1 << 5);
                }
        }
}

int main(void)
{

        tick = 0;

        DDRB |= 1<<5;

        init_kernel();

        set_task(&led_on, 0);
        set_task(&led_off, 1);

        run_kernel();

        while (1) {
                wdt_reset();
                asm("nop");
        }

        return 0;
}
