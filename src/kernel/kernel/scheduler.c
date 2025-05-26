#include <idt.h>
#include <scheduler.h>
#include <stdlib.h>
#define MAX_PROCESSES 32

// Currently active processes
struct process_t *processes_list = NULL;

volatile struct process_t *current_process = NULL;
size_t next_free_pid = 0;

volatile struct process_t process_table[MAX_PROCESSES];
size_t next_free_process = 0;

void add_process(struct process_t *new_process)
{
    if (processes_list == NULL)
    {
        new_process->next = NULL;
        processes_list = new_process;
    }
    else
    {
        // process_t *tail = NULL;
        // if (processes_list->prev)
        // {
        // tail = processes_list->prev;
        // }
        // else
        // {
        // tail = processes_list;
        // }
        // processes_list->prev = new_process;
        new_process->next = processes_list;
        processes_list = new_process;
        // processes_list->prev = tail;
        // tail->next = processes_list;
    }
}

void delete_process(struct process_t *process)
{
    process->prev->next = process->next;
    process->next->prev = process->prev;
}

struct process_t *get_next_process()
{
    return processes_list->prev;
}

void copy_context(struct cpu_status_t prev_context, struct cpu_status_t *new_context)
{
    new_context->edi = prev_context.edi;
    new_context->esi = prev_context.esi;
    new_context->esp = prev_context.esp;
    new_context->ebp = prev_context.ebp;
    new_context->ebx = prev_context.ebx;
    new_context->edx = prev_context.edx;
    new_context->ecx = prev_context.ecx;
    new_context->eax = prev_context.eax;
    new_context->eip = prev_context.eip;
    new_context->cs = 0x08;
    new_context->eflags = 0x202;
}

struct cpu_status_t *schedule(struct cpu_status_t *context)
{
    // current_process->context = *context;
    // Copy current context to restore it later
    copy_context(*context, &current_process->context);
    // current_process->status = READY;

    // Alloc private space for the process
    struct cpu_status_t *allocated_context = malloc(sizeof(struct cpu_status_t));

    if (current_process == NULL)
    {
        current_process = processes_list;
    }

    if (current_process->next != NULL)
    {
        current_process = current_process->next;
    }
    else
    {
        current_process = processes_list;
    }

    // Return a heap copy of the process information to keep the original PCB safe
    copy_context(current_process->context,allocated_context);

    return allocated_context;
}

struct process_t *create_process(char *name, void (*function)(void *), void *arg)
{
    struct process_t *process = &process_table[next_free_process++];
    struct cpu_status_t new_context = process->context;

    // strncpy(process->name, name, NAME_MAX_LEN);
    process->pid = next_free_pid++;
    process->status = READY;
    // Kernel stack segment
    // process->context->esp = alloc_stack();
    new_context.esp = (uint32_t)&process->stack + 8192;
    new_context.eflags = 0x202;
    // Kernel code segment
    new_context.cs = 0x08;
    new_context.eip = (uint32_t)function; // Instruction pointer (EIP)
    // new_context->edi = (uint32_t)arg;
    new_context.edi = 0x0;             // First argument (EDI)
    new_context.ebp = new_context.esp; // Base pointer reset
    process->context = new_context;

    add_process(process);

    return process;
}