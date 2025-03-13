#include <stdint.h>

// const int NAME_MAX_LEN = 64;
#define PROCESS_STACK_SIZE 8192 

typedef enum
{
    READY,
    RUNNING,
    DEAD
} status_t;

struct process_t
{
    size_t pid;
    status_t status;
    struct cpu_status_t *context;
    char name[64];
    struct process_t *next;
    struct process_t *prev;
    uint8_t stack[PROCESS_STACK_SIZE]; 
} __attribute__((packed));

struct cpu_status_t
{
    uint32_t edi;
    uint32_t esi;
    void *esp;
    void *ebp;
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;
    uint32_t *eip;
    uint32_t cs;
    uint32_t eflags;
} __attribute__((packed));

struct cpu_status_t *schedule(struct cpu_status_t *context);
struct process_t *create_process(char *name, void (*function)(void *), void *arg);