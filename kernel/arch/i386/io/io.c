#include <kernel/io.h>

// This function reads a byte from an IO Port (memory address)
inline uint8_t inb(uint16_t port)
{
    // The bytes read will be stored on the "ret" variable
    uint8_t ret;
    __asm__ volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

// This function writes a byte into an IO Port
inline void outb(uint16_t port, uint8_t value)
{
    __asm__ volatile("outb %0, %1" : : "a"(value), "Nd"(port));
}

inline void io_wait(void)
{
    outb(0x80, 0);
}