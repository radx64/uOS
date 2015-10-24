#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#define COLUMNS 80
#define ROWS 25
#define CELL_SIZE 2
#define FB_ADDRESS 0x000B8000

typedef enum 
{
    C_BLACK   = 0x0,
    C_BLUE    = 0x1,
    C_GREEN   = 0x2,
    C_CYAN    = 0x3,
    C_RED     = 0x4,
    C_MAGENTA = 0x5,
    C_BROWN   = 0x6,
    C_LIGHT_GREY    = 0x7, 
    C_DARK_GREY     = 0x8,
    C_LIGHT_BLUE    = 0x9,
    C_LIGHT_GREEN   = 0xA,
    C_LIGHT_CYAN    = 0xB,
    C_LIGHT_RED     = 0xC,
    C_LIGHT_MAGENTA = 0xD,
    C_LIGHT_BROWN   = 0xE,
    C_WHITE         = 0xF
} Color;

void fb_write_cell(
    unsigned int location,
    char character,
    Color foreground,
    Color background);

void fb_write_cell_xy(
    unsigned char x,
    unsigned char y,
    char character,
    Color foreground,
    Color background);

void fb_clear();

void fb_set_colors(Color foreground, Color background);

void fb_move_cursor(unsigned int position);

void fb_move_cursor_xy(unsigned char x, unsigned char y);

void fb_scroll_up();

void write(char* buffer, unsigned int length);

#endif // FRAMEBUFFER_H