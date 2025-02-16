#define MULTIBOOT_TAG_TYPE_FRAMEBUFFER 8
#include <stdint.h>

struct multiboot_tag {
    uint32_t type;
    uint32_t size;
};

struct multiboot_tag_framebuffer {
    uint32_t type;
    uint32_t size;
    uint64_t framebuffer_addr;
    uint32_t framebuffer_pitch;
    uint32_t framebuffer_width;
    uint32_t framebuffer_height;
    uint8_t framebuffer_bpp;
    uint8_t framebuffer_type;
    uint8_t reserved;
};

// PSF Font struct
#include <stdint.h>

struct PSF1_HEADER {
        unsigned char magic[2];     /* Magic number */
        unsigned char mode;         /* PSF font mode */
        unsigned char charsize;     /* Character size */
};



void init_framebuffer(void* multiboot_addr);
