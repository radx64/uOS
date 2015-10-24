#ifndef VGA_H
#define VGA_H

#define COLUMNS 80
#define ROWS 25
#define CELL_SIZE 2
#define TAB_WIDTH 4
#define VGA_ADDRESS 0x000B8000

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

void vga_write_cell(
    unsigned int location,
    char character,
    Color foreground,
    Color background);

void vga_write_cell_xy(
    unsigned char x,
    unsigned char y,
    char character,
    Color foreground,
    Color background);

void vga_clear();

void vga_set_colors(Color foreground, Color background);

void vga_move_cursor(unsigned int position);

void vga_move_cursor_xy(unsigned char x, unsigned char y);

void vga_scroll_up();

void vga_write(char* buffer, unsigned int length);

#endif // VGA_H