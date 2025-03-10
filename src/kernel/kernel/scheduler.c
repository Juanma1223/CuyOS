#include <idt.h>
#include <scheduler.h>

// Currently active processes
process_t *processes_list = NULL;

process_t *current_process = NULL;
size_t next_free_pid = 0;

void add_process(process_t *new_process)
{
    if (processes_list == NULL)
    {
        new_process->next = NULL;
        processes_list = new_process;
    }
    else
    {
        process_t *tail = NULL;
        if (processes_list->prev)
        {
            tail = processes_list->prev;
        }
        else
        {
            tail = processes_list;
        }
        processes_list->prev = new_process;
        new_process->next = processes_list;
        processes_list = new_process;
        processes_list->prev = tail;
        tail->next = processes_list;
    }
}

void delete_process(process_t *process)
{
    process->prev->next = process->next;
    process->next->prev = process->prev;
}

process_t *get_next_process()
{
    return processes_list->prev;
}

struct cpu_status_t *schedule(struct cpu_status_t *context)
{
    process_t *prempted_process;
    current_process->context = context;
    current_process->status = READY;

    if (current_process == NULL)
    {
        current_process = processes_list;
        return current_process->context;
    }

    if (current_process->next != NULL)
    {
        current_process = current_process->next;
    }

    // This loop checks dead processes and kills them
    // while (1)
    // {
    //     process_t *prev_process = current_process;
    //     if (current_process->next != NULL && current_process->next != current_process)
    //     {
    //         current_process = current_process->next;
    //     }
    //     else
    //     {
    //         current_process = processes_list;
    //     }

    //     if (current_process != NULL && current_process->status == DEAD)
    //     {
    //         // We need to delete dead processes
    //         delete_process(current_process);
    //     }
    //     else
    //     {

    //         current_process->status = RUNNING;
    //         break;
    //     }
    // }
    return current_process->context;
}

process_t *create_process(char *name, void (*function)(void *), void *arg)
{
    process_t *process;

    struct cpu_status_t *new_context;

    // strncpy(process->name, name, NAME_MAX_LEN);
    process->pid = next_free_pid++;
    process->status = READY;
    // Kernel stack segment
    new_context->ss = 0x10;
    // process->context->esp = alloc_stack();
    new_context->esp = (uint32_t)function;
    new_context->eflags = 0x202;
    // Kernel code segment
    new_context->cs = 0x08;
    new_context->eip = (uint32_t)function; // Instruction pointer (EIP)
    new_context->edi = (uint32_t)arg;      // First argument (EDI)
    new_context->ebp = 0;                  // Base pointer reset
    process->context = new_context;

    add_process(process);

    return process;
}