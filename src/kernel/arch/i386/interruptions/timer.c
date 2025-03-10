#include <stdint.h>
#include <stdio.h>
#include <scheduler.h>

volatile uint32_t timer_ticks = 0;

void print_cpu_status(struct cpu_status_t *context)
{
    printf("CPU Context Dump:\n");
    printf("SS:          %p -> %p \n", &context->ss, context->ss);
    printf("User ESP:    %p -> %p \n", &context->user_esp, context->user_esp);
    // printf("EFLAGS:      %p -> %p \n", &context->eflags, context->eflags);
    // printf("CS:          %p -> %p\n", &context->cs, context->cs);
    // printf("EIP:         %p -> %p\n", &context->eip, context->eip);
    // printf("Error Code:  %p -> %p\n", &context->error_code, context->error_code);
    // printf("Interrupt #: %p -> %p\n", &context->interrupt_number, context->interrupt_number);
    printf("Falopa  %p\n", context->falopa2);
    printf("EAX:         %p -> %p\n", &context->eax, context->eax);
    printf("ECX:         %p -> %p\n", &context->ecx, context->ecx);
    printf("EDX:         %p -> %p\n", &context->edx, context->edx);
    printf("EBX:         %p -> %p\n", &context->ebx, context->ebx);
    printf("Old ESP:     %p -> %p\n", &context->esp, context->esp);
    printf("ESI:         %p -> %p\n", &context->esi, context->esi);
    printf("EBP:         %p -> %p\n", &context->ebp, context->ebp);
    printf("Function pointer  %p\n", context->eip);
    printf("EDI:         %p -> %p\n", &context->edi, context->edi);

    // printf("GS:          %p -> %p\n", &context->gs, context->gs);
    // printf("FS:          %p -> %p\n", &context->fs, context->fs);
    // printf("ES:          %p -> %p\n", &context->es, context->es);
    // printf("DS:          %p -> %p\n", &context->ds, context->ds);
}

// Function called by the assembly ISR when a timer interrupt occurs
struct cpu_status_t *timerHandler(struct cpu_status_t *context)
{
    timer_ticks++;
    // printf("ESP expected: %p | Received: %p\n", &context->edi, context);
    print_cpu_status(context);
    // Every 10 ticks, fire the scheduler
    // if (timer_ticks % 10 == 0)
    // {
    return schedule(context);
    // }
    return context;
}
