#include "framebuffer.h"

#include "io.h"

/*
Framebuffer address: 0x000B8000
Framebuffer cell structure
Bit:        |15 14 13 12 11 10  9  8| 7  6  5  4  3  2  1  0|
Content:    |ASCII CODE OF CHARACTER|   FG      |     BG    |
*/

void fb_write_cell(
    unsigned int location,
    char character,
    unsigned char foreground,
    unsigned char background)
{
    char* fb = (char *) 0x000B8000;
    unsigned int offset = location * CELL_SIZE;
    fb[offset] = character;
    fb[offset+1] = (foreground & 0x0F) | ((background * 0x0F)<< 4);
} 

void fb_write_at_location(
    unsigned char x,
    unsigned char y,
    char character,
    unsigned char
    foreground,
    unsigned char background)
{
    if ((x > COLUMNS-1) || (y > ROWS-1))
    {
        return;     // early exit when incorrect parameters given
    }

    unsigned int offset = COLUMNS * y + x;
    fb_write_cell(offset, character, foreground, background);
}

void fb_clear()
{
    for(int offset = 0; offset <= COLUMNS*ROWS; offset++)
    {
        fb_write_cell(offset,0, 0xF, 0x0);  
    }
}

void fb_move_cursor(unsigned char x, unsigned char y)
{
    #define FB_COMMAND_PORT 0x3D4
    #define FB_DATA_PORT    0x3D5

    #define FB_HIGH_BYTE_COMMAND 0x0E
    #define FB_LOW_BYTE_COMMAND  0x0F

    unsigned short position = y*COLUMNS + x;

    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT, position & 0xFF);
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT, (position >> 8) & 0xFF);
}
