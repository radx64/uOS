#include <string.h>

#include "vga.h"
#include "io.h"

/*
Framebuffer address: 0x000B8000
Framebuffer cell structure
Bit:        |15 14 13 12 11 10  9  8| 7  6  5  4  3  2  1  0|
Content:    |ASCII CODE OF CHARACTER|   FG      |     BG    |
*/

uint16_t vga_currentCell = 0;
Color vga_foreground = C_WHITE;
Color vga_background = C_BLACK;

void vga_set_colors(Color foreground, Color background)
{
    vga_foreground = foreground;
    vga_background = background;
}

void vga_write_cell(
    uint32_t location,
    int8_t character,
    Color foreground,
    Color background)
{
    int8_t* fb = (int8_t *) VGA_ADDRESS;
    uint32_t offset = location * CELL_SIZE;
    fb[offset] = character;
    fb[offset+1] = (foreground & 0x0F) | ((background & 0x0F) << 4);
} 

void vga_write_cell_xy(
    uint8_t x,
    uint8_t y,
    int8_t character,
    Color foreground,
    Color background)
{
    if ((x > COLUMNS-1) || (y > ROWS-1))
    {
        return;     // early exit when incorrect parameters given
    }

    uint32_t offset = COLUMNS * y + x;
    vga_write_cell(offset, character, foreground, background);
}

void vga_clear()
{
    for(int offset = 0; offset <= COLUMNS*ROWS; offset++)
    {
        vga_write_cell(offset,0, C_WHITE, C_BLACK);  
    }
}

void vga_move_cursor(uint32_t position)
{
    #define vga_COMMAND_PORT 0x3D4
    #define vga_DATA_PORT    0x3D5

    #define vga_HIGH_BYTE_COMMAND 0x0E
    #define vga_LOW_BYTE_COMMAND  0x0F

    outb(vga_COMMAND_PORT, vga_LOW_BYTE_COMMAND);
    outb(vga_DATA_PORT, position & 0xFF);
    outb(vga_COMMAND_PORT, vga_HIGH_BYTE_COMMAND);
    outb(vga_DATA_PORT, (position >> 8) & 0xFF);
}

void vga_move_cursor_xy(uint8_t x, uint8_t y)
{
    uint16_t position = y*COLUMNS + x;
    vga_move_cursor(position);
}

void vga_scroll_up()
{
    int8_t* fb = (int8_t *) VGA_ADDRESS;
    for (uint32_t i = 0; i < COLUMNS*(ROWS-1)*CELL_SIZE;++i)
    {
        fb[i] = fb[i+COLUMNS*CELL_SIZE];  
    }

    for (uint32_t i = COLUMNS*(ROWS-1); i < COLUMNS*ROWS;i++)
    {
        vga_write_cell(i,0, C_WHITE, C_BLACK);  
    }  
}

void vga_write(int8_t* buffer)
{
    uint32_t length = strlen(buffer);

    for (uint32_t i = 0; i< length; ++i)
    {
        if (buffer[i] == '\n')
        {
            vga_currentCell = (vga_currentCell - (vga_currentCell % COLUMNS)) + COLUMNS;
            continue;
        }
        if (buffer[i] == '\t')
        {
            vga_currentCell = vga_currentCell - (vga_currentCell % TAB_WIDTH) + TAB_WIDTH;
            continue;
        } 
        if (vga_currentCell >= ROWS*COLUMNS)
        {
            vga_scroll_up();
            vga_currentCell = vga_currentCell - COLUMNS;
        }
        vga_write_cell(vga_currentCell++,buffer[i], vga_foreground, vga_background);
    }
    vga_move_cursor(vga_currentCell);
}