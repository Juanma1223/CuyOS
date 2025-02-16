#include <screen_driver.h>
#include <image.h>

const int GREEN = 0x00FF00;

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
            uint32_t pixel_pos = (i * (fb->framebuffer_pitch / 4)) + j; // (pitch / 4) for 32-bit pixels
            uint64_t *fb_addr = (uint64_t *)fb->framebuffer_addr;
            fb_addr[pixel_pos] = num; // Set pixel color
        }
    }
}

void draw_square(uint64_t *fb, uint32_t pitch, uint32_t x, uint32_t y, uint32_t size, uint32_t color)
{
    for (uint32_t row = 0; row < size; row++)
    {
        for (uint32_t col = 0; col < size; col++)
        {
            uint32_t pixel_pos = ((y + row) * (pitch / 4)) + (x + col); // (pitch / 4) for 32-bit pixels
            fb[pixel_pos] = color;                                      // Set pixel color
        }
    }
}

void draw_char(struct multiboot_tag_framebuffer *fb, uint8_t *character, uint16_t x, uint16_t y)
{
    for (int row = 0; row < 16; row++)
    {
        uint8_t bitmap = character[row];
        for (int col = 0; col < 8; col++)
        {
            // Bitmap is in base 2
            int pixel = bitmap % 2;
            if (pixel == 1)
            {
                uint32_t pixel_pos = (((y * 20) + row) * (fb->framebuffer_pitch / 4)) + col + (x * 10); // (pitch / 4) for 32-bit pixels
                uint64_t *fb_addr = (uint64_t *)fb->framebuffer_addr;
                fb_addr[pixel_pos] = GREEN; // Set pixel color
            }
            bitmap = bitmap / 2;
        }
        // Go to the following bitmap
    }
    character = character + 1;
}

void setup_text_font(struct multiboot_tag_framebuffer *fb)
{
    // Font has been linked into the binary
    extern char _binary_font_psf_start;
    struct PSF1_HEADER *default_font = (struct PSF1_HEADER *)&_binary_font_psf_start;
    for (int y = 0; y < 20; y++)
    {
        for (int x = 0; x < 20; x++)
        {
            uint8_t *glyph_address = (uint8_t *)&_binary_font_psf_start + (16 * x * (y + 1));
            uint8_t *selected_glyph_v1 = (uint8_t *)&_binary_font_psf_start +
                                         sizeof(struct PSF1_HEADER) + (x * 128);
            draw_char(fb, glyph_address, x, y);
        }
    }
}

void init_framebuffer(void *multiboot_addr)
{
    struct multiboot_tag *tag;
    for (tag = (struct multiboot_tag *)(multiboot_addr + 8);
         tag->type != 0;
         tag = (struct multiboot_tag *)((uint8_t *)tag + ((tag->size + 7) & ~7)))
    {

        if (tag->type == MULTIBOOT_TAG_TYPE_FRAMEBUFFER)
        {
            struct multiboot_tag_framebuffer *fb = (struct multiboot_tag_framebuffer *)tag;
            // Now you have access to framebuffer information
            uint64_t *fb_addr = (uint64_t *)fb->framebuffer_addr;
            uint32_t fb_width = fb->framebuffer_width;
            uint32_t fb_height = fb->framebuffer_height;
            uint32_t fb_pitch = fb->framebuffer_pitch;
            uint8_t fb_bpp = fb->framebuffer_bpp;

            // Use this information to set up your display
            // draw_square(fb_addr, fb_pitch, 0, 0, 50, 0x00FF00);
            setup_text_font(fb);
            // test_draw(fb);
        }
    }
}