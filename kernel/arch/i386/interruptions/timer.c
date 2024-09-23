#include <stdint.h>
#include <stdio.h>

volatile uint32_t timer_ticks = 0;

// Function called by the assembly ISR when a timer interrupt occurs
void timerHandler() {
    timer_ticks++;
    if (timer_ticks % 100 == 0) {  // Print every 100 ticks
        printf("Timer ticks: %d\n", timer_ticks);
    }
}
