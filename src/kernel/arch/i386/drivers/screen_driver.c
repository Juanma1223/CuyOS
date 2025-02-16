#include <screen_driver.h>
#include <image.h>

const int WHITE = 0xFFFFFF;
const int BLACK = 0x000000;

// Lookup table for font characters positions
char characters_table[128] = {
    [0] = '\0', [1] = '\x01', [2] = '\x02', [3] = '\x03', [4] = '\x04', [5] = '\x05', [6] = '\x06', [7] = '\x07', [8] = '\b', [9] = '\t', [10] = '\n', [11] = '\v', [12] = '\f', [13] = '\r', [14] = '\x0E', [15] = '\x0F', [16] = '\x10', [17] = '\x11', [18] = '\x12', [19] = '\x13', [20] = '\x14', [21] = '\x15', [22] = '\x16', [23] = '\x17', [24] = '\x18', [25] = '\x19', [26] = '\x1A', [27] = '\x1B', [28] = '\x1C', [29] = '\x1D', [30] = '\x1E', [31] = '\x1F', [32] = ' ', [33] = '!', [34] = '"', [35] = '#', [36] = '$', [37] = '%', [38] = '&', [39] = '\'', [40] = '(', [41] = ')', [42] = '*', [43] = '+', [44] = ',', [45] = '-', [46] = '.', [47] = '/', [48] = '0', [49] = '1', [50] = '2', [51] = '3', [52] = '4', [53] = '5', [54] = '6', [55] = '7', [56] = '8', [57] = '9', [58] = ':', [59] = ';', [60] = '<', [61] = '=', [62] = '>', [63] = '?', [64] = '@', [65] = 'A', [66] = 'B', [67] = 'C', [68] = 'D', [69] = 'E', [70] = 'F', [71] = 'G', [72] = 'H', [73] = 'I', [74] = 'J', [75] = 'K', [76] = 'L', [77] = 'M', [78] = 'N', [79] = 'O', [80] = 'P', [81] = 'Q', [82] = 'R', [83] = 'S', [84] = 'T', [85] = 'U', [86] = 'V', [87] = 'W', [88] = 'X', [89] = 'Y', [90] = 'Z', [91] = '[', [92] = '\\', [93] = ']', [94] = '^', [95] = '_', [96] = '`', [97] = 'a', [98] = 'b', [99] = 'c', [100] = 'd', [101] = 'e', [102] = 'f', [103] = 'g', [104] = 'h', [105] = 'i', [106] = 'j', [107] = 'k', [108] = 'l', [109] = 'm', [110] = 'n', [111] = 'o', [112] = 'p', [113] = 'q', [114] = 'r', [115] = 's', [116] = 't', [117] = 'u', [118] = 'v', [119] = 'w', [120] = 'x', [121] = 'y', [122] = 'z', [123] = '{', [124] = '|', [125] = '}', [126] = '~', [127] = '\x7F'};

// Framebuffer address
struct multiboot_tag_framebuffer *fb;

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

void draw_char(char character, uint16_t x, uint16_t y)
{
    // Get font memory positionn
    extern char _binary_font_psf_start;
    uint8_t *selected_glyph = (uint8_t *)&_binary_font_psf_start +
                              sizeof(struct PSF1_HEADER) + (16 * characters_table[character]);
    for (int row = 0; row < 16; row++)
    {
        uint8_t bitmap = selected_glyph[row];
        for (int col = 0; col < 8; col++)
        {
            // Bitmap is in base 2
            int pixel = (bitmap >> (7 - col)) & 1;
            uint32_t pixel_pos = (((y * 16) + row) * (fb->framebuffer_pitch / 4)) + col + (x * 10); // (pitch / 4) for 32-bit pixels
            uint64_t *fb_addr = (uint64_t *)fb->framebuffer_addr;
            if (pixel == 1)
            {
                fb_addr[pixel_pos] = WHITE; // Set pixel color
            }
            else
            {
                fb_addr[pixel_pos] = BLACK; // Set pixel color
            }
        }
        // Go to the following bitmap
    }
    selected_glyph = selected_glyph + 1;
}

void setup_text_font()
{
    // Font has been linked into the binary
    draw_char('a', 0, 0);
    draw_char('b', 1, 0);
    draw_char('c', 2, 0);
    draw_char('d', 3, 0);
    draw_char('e', 4, 0);
    draw_char('f', 5, 0);
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
            struct multiboot_tag_framebuffer *framebuffer = (struct multiboot_tag_framebuffer *)tag;
            uint64_t *fb_addr = (uint64_t *)framebuffer->framebuffer_addr;
            uint32_t fb_width = framebuffer->framebuffer_width;
            uint32_t fb_height = framebuffer->framebuffer_height;
            uint32_t fb_pitch = framebuffer->framebuffer_pitch;
            uint8_t fb_bpp = framebuffer->framebuffer_bpp;

            // Use this information to set up your display
            // draw_square(fb_addr, fb_pitch, 0, 0, 50, 0x00FF00);
            fb = framebuffer;
            // setup_text_font();
            // test_draw(fb);
        }
    }
}