#include <stdint.h>

const NAME_MAX_LEN = 64;

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
    char name[NAME_MAX_LEN];
    struct process_t *next;
    struct process_t *prev;
} process_t;

// This structure holds the cpu status on a given moment
struct cpu_status_t {
    uint32_t edi; // Callee-saved register
    uint32_t esi; // Callee-saved register
    uint32_t ebp; // Base pointer
    uint32_t esp; // Stack pointer (optional, usually managed by hardware)
    uint32_t ebx; // Callee-saved register
    uint32_t edx; // Data register
    uint32_t ecx; // Counter register
    uint32_t eax; // Accumulator register

    uint32_t vector_number; // Interrupt vector number
    uint32_t error_code;    // Error code (if applicable)

    uint32_t iret_eip;   // Return instruction pointer
    uint32_t iret_cs;    // Code segment
    uint32_t iret_eflags;// CPU flags
    uint32_t iret_esp;   // Stack pointer at interrupt time
    uint32_t iret_ss;    // Stack segment
};

struct cpu_status_t *schedule(struct cpu_status_t *context);