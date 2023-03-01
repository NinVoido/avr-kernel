#include <avr/io.h>
#include <avr/wdt.h>

#include "./os/kernel.h"
#include "./os/config.h"

ISR(kernel_interrupt)
{
        /* TODO - turn off the LED here to check if this actually executes */
        timer_service();
}

void led_off(void);
void led_on(void);

void led_on(void)
{
        set_timer_task(led_off, 300);
        PORTB ^= 1<<5;
}

void led_off(void)
{
        set_timer_task(led_on, 300);
        PORTB &= ~(1<<5);
}

int main(void)
{
        /* TODO - move hardware-specific setup to another file */
        DDRB |= 1<<5;

        init_kernel();
        run_kernel();

        set_task(led_on);

        while (1) {
                wdt_reset();
                task_manager();
        }

        return 0;
}
