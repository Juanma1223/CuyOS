#define MULTIBOOT_TAG_TYPE_FRAMEBUFFER 8
#include <stdint.h>

struct multiboot_tag
{
    uint32_t type;
    uint32_t size;
};

// RGB color constants for terminal use
#define WHITE        0xFFFFFF
#define BLACK        0x000000
#define RED          0xFF0000
#define GREEN        0x00FF00
#define BLUE         0x0000FF
#define CYAN         0x00FFFF
#define MAGENTA      0xFF00FF
#define YELLOW       0xFFFF00
#define BROWN        0xA52A2A
#define LIGHT_GREY   0xD3D3D3
#define DARK_GREY    0xA9A9A9
#define LIGHT_BLUE   0xADD8E6
#define LIGHT_GREEN  0x90EE90
#define LIGHT_CYAN   0xE0FFFF
#define LIGHT_RED    0xFFA07A
#define LIGHT_MAGENTA 0xFF77FF

struct multiboot_tag_framebuffer
{
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

struct PSF1_HEADER
{
    unsigned char magic[2]; /* Magic number */
    unsigned char mode;     /* PSF font mode */
    unsigned char charsize; /* Character size */
};

void init_framebuffer(void *multiboot_addr);
void draw_char(char character, uint16_t x, uint16_t y, int color);