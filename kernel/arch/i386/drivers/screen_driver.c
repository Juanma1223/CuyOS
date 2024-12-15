#include <kernel/screen_driver.h>
#include <kernel/image.h>

uint32_t * calculatePixel(int x, int y, struct multiboot_tag_framebuffer *fb)
{
    int row = y * fb->framebuffer_pitch;
    int column = x * fb->framebuffer_bpp;
    uint32_t *pixel = (uint32_t *)((char *)fb + row + column);
    return pixel;
}

void test_draw(struct multiboot_tag_framebuffer *fb)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            unsigned char pixel[4];
            HEADER_PIXEL(header_data, pixel)
            pixel[3] = 0;
            uint32_t num = (uint32_t)pixel[3] << 24 |
                           (uint32_t)pixel[0] << 16 |
                           (uint32_t)pixel[1] << 8 |
                           (uint32_t)pixel[2];
            uint32_t *targetPixel = calculatePixel(i, j, fb);
            targetPixel = &num;
        }
    }
}

void parse_multiboot(uint32_t addr)
{
    struct multiboot_tag *tag;
    for (tag = (struct multiboot_tag *)(addr + 8);
         tag->type != 0;
         tag = (struct multiboot_tag *)((uint8_t *)tag + ((tag->size + 7) & ~7)))
    {

        if (tag->type == MULTIBOOT_TAG_TYPE_FRAMEBUFFER)
        {
            struct multiboot_tag_framebuffer *fb = (struct multiboot_tag_framebuffer *)tag;
            // Now you have access to framebuffer information
            uint64_t fb_addr = fb->framebuffer_addr;
            uint32_t fb_width = fb->framebuffer_width;
            uint32_t fb_height = fb->framebuffer_height;
            uint32_t fb_pitch = fb->framebuffer_pitch;
            uint8_t fb_bpp = fb->framebuffer_bpp;

            // Use this information to set up your display
            test_draw(fb);
        }
    }
}