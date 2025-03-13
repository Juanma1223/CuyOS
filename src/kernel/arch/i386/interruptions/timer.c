#include <stdint.h>
#include <stdio.h>
#include <scheduler.h>

volatile uint32_t timer_ticks = 0;

void print_cpu_status(struct cpu_status_t *context)
{
    printf("CPU Context Dump:\n");
    // printf("CS:          %p -> %p\n", &context->cs, context->cs);
    // printf("EFLAGS:      %p -> %p \n", &context->eflags, context->eflags);
    printf("EIP:         %p -> %p\n", &context->eip, context->eip);
    printf("EAX:         %p -> %p\n", &context->eax, context->eax);
    printf("ECX:         %p -> %p\n", &context->ecx, context->ecx);
    printf("EDX:         %p -> %p\n", &context->edx, context->edx);
    printf("EBX:         %p -> %p\n", &context->ebx, context->ebx);
    printf("Old ESP:     %p -> %p\n", &context->esp, context->esp);
    printf("ESI:         %p -> %p\n", &context->esi, context->esi);
    printf("Old EBP:         %p -> %p\n", &context->ebp, context->ebp);
    printf("EDI:         %p -> %p\n", &context->edi, context->edi);
    printf("CS:         %p -> %p\n", &context->cs, context->cs);
    printf("EFLAGS:         %p -> %p\n", &context->eflags, context->eflags);
}

// Function called by the assembly ISR when a timer interrupt occurs
struct cpu_status_t *timerHandler(struct cpu_status_t *context)
{
    timer_ticks++;
    // printf("ESP expected: %p | Received: %p\n", &context->edi, context);
    // print_cpu_status(context);
    // Every 10 ticks, fire the scheduler
    if (timer_ticks % 20 == 0)
    {
        printf("Schedule! \n");
        return schedule(context);
    }
    return context;
}
