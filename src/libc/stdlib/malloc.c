#include <stdint.h>
#include <stddef.h>

#define HEAP_START  0x01000000  // Heap starts at 16 MB
#define HEAP_SIZE   0x00100000  // 1 MB heap
#define BLOCK_SIZE  16          // Minimum allocation block

static uint8_t *heap = (uint8_t *)HEAP_START;  // Heap base pointer
static uint32_t heap_top = HEAP_START;  // Tracks the top of allocated memory

void *malloc(uint32_t size) {
    if (heap_top + size > HEAP_START + HEAP_SIZE) {
        return NULL;  // Out of memory
    }
    
    void *allocated = (void *)heap_top;
    heap_top += size;

    return allocated;
}