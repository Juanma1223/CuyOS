#include <stdint.h>
// In this file we define functions and structs to interact with the Global Descriptor table

#define GDT_DESCRIPTORS_QUANTITY 0x05
#define ACCESS_KERNEL_CODE 0x9A // 0x9A = 10011010b
#define ACCESS_KERNEL_DATA 0x92 // 0x92 = 10010010b
#define ACCESS_USER_CODE 0xFA   // 0xFA = 11111010b
#define ACCESS_USER_DATA 0xF2   // 0xF2 = 11110010b

#define FLAGS_GRANULARITY 0x0C // Granularity = 1 (4KB blocks), 32-bit mode

#define SEGMENT_BASE 0x00000000
#define SEGMENT_LIMIT 0xFFFFF // 4GB allocated space

// This struct is encoded to be placed into the GDT, it is required to be 8 bytes long
typedef struct GDT_entry
{
    int limit;
    uint16_t base;
    uint16_t access_byte;
    uint16_t flags;
} __attribute__((packed));

struct GDTR
{
    uint16_t limit;
    uintptr_t base;
} __attribute__((packed));

void encodeGdtEntry(uint8_t *target, struct GDT_entry source);
void setupGDT();