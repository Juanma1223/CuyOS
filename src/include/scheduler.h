#include <stdint.h>

// const int NAME_MAX_LEN = 64;

typedef enum
{
    READY,
    RUNNING,
    DEAD
} status_t;

typedef struct process_t
{
    size_t pid;
    status_t status;
    struct cpu_status_t *context;
    char name[64];
    struct process_t *next;
    struct process_t *prev;
} process_t;

// This structure holds the cpu status on a given moment
// struct cpu_status_t
// {
//     uint32_t ss;         // Pushed by CPU (only if switching from user mode)
//     uint32_t user_esp;   // Only if switching from user mode
//     uint32_t eip;        // Pushed by CPU
//     uint32_t error_code; // Only for some exceptions
//     uint32_t interrupt_number;

//     uint32_t eax; // Last register pushed by pusha
//     uint32_t ecx;
//     uint32_t edx;
//     uint32_t ebx;
//     uint32_t esp; // ESP before pusha
//     uint32_t ebp;
//     uint32_t esi;
//     uint32_t cs;  // Pushed by CPU
//     uint32_t edi; // First register pushed by pusha

//     // uint32_t gs;     // Manually pushed segment registers
//     uint32_t eflags; // Pushed by CPU
//     // uint32_t fs;
//     // uint32_t es;
//     // uint32_t ds; // First value pushed (highest address)
// };

struct cpu_status_t
{
    uint32_t ss;
    uint32_t user_esp;
    uint32_t esp; // ESP before pusha
    uint32_t falopa2;
    uint32_t eflags; // Pushed by CPU
    uint32_t ebx;
    uint32_t eax;    // Last register pushed by pusha
    uint32_t ecx;
    uint32_t edx;
    uint32_t cs;
    uint32_t esi;      // Pushed by CPU
    uint32_t ebp;
    uint32_t eip;
    uint32_t edi; // First register pushed by pusha

    // uint32_t gs;     // Manually pushed segment registers
    // uint32_t fs;
    // uint32_t es;
    // uint32_t ds; // First value pushed (highest address)
};

struct cpu_status_t *schedule(struct cpu_status_t *context);
process_t *create_process(char *name, void (*function)(void *), void *arg);