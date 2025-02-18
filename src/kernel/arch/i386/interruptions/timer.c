#include <stdint.h>
#include <stdio.h>
#include <scheduler.h>

volatile uint32_t timer_ticks = 0;

// Function called by the assembly ISR when a timer interrupt occurs
void timerHandler(struct cpu_status_t *context) {
    timer_ticks++;
    // Every 10 ticks, fire the scheduler
    if (timer_ticks % 10 == 0) {  
        schedule(context);
    }
}
