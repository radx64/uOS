#include "framebuffer.h"
#include "io.h"

/*
Framebuffer address: 0x000B8000
Framebuffer cell structure
Bit:        |15 14 13 12 11 10  9  8| 7  6  5  4  3  2  1  0|
Content:    |ASCII CODE OF CHARACTER|   FG      |     BG    |
*/

unsigned short fb_currentCell = 0;
Color fb_foreground = C_WHITE;
Color fb_background = C_BLACK;

void fb_set_colors(Color foreground, Color background)
{
    fb_foreground = foreground;
    fb_background = background;
}

void fb_write_cell(
    unsigned int location,
    char character,
    Color foreground,
    Color background)
{
    char* fb = (char *) FB_ADDRESS;
    unsigned int offset = location * CELL_SIZE;
    fb[offset] = character;
    fb[offset+1] = (foreground & 0x0F) | ((background * 0x0F)<< 4);
} 

void fb_write_cell_xy(
    unsigned char x,
    unsigned char y,
    char character,
    Color foreground,
    Color background)
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
        fb_write_cell(offset,0, C_WHITE, C_BLACK);  
    }
}

void fb_move_cursor(unsigned int position)
{
    #define FB_COMMAND_PORT 0x3D4
    #define FB_DATA_PORT    0x3D5

    #define FB_HIGH_BYTE_COMMAND 0x0E
    #define FB_LOW_BYTE_COMMAND  0x0F

    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT, position & 0xFF);
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT, (position >> 8) & 0xFF);
}

void fb_move_cursor_xy(unsigned char x, unsigned char y)
{
    unsigned short position = y*COLUMNS + x;
    fb_move_cursor(position);
}

void fb_scroll_up()
{
    char* fb = (char *) FB_ADDRESS;
    for (unsigned int i = 0; i < COLUMNS*(ROWS-1)*CELL_SIZE;++i)
    {
        fb[i] = fb[i+COLUMNS*CELL_SIZE];  
    }

    for (unsigned int i = COLUMNS*(ROWS-1); i < COLUMNS*ROWS;i++)
    {
        fb_write_cell(i,0, C_WHITE, C_BLACK);  
    }  
}

void write(char* buffer, unsigned int length)
{
    for (unsigned int i = 0; i< length; ++i)
    {
        if (buffer[i] == '\n')
        {
            fb_currentCell = (fb_currentCell - (fb_currentCell % COLUMNS)) + COLUMNS;
            continue;
        }
        if (buffer[i] == '\t')
        {
            fb_currentCell = fb_currentCell - (fb_currentCell % TAB_WIDTH) + TAB_WIDTH;
            continue;
        } 
        if (fb_currentCell >= ROWS*COLUMNS)
        {
            fb_scroll_up();
            fb_currentCell = fb_currentCell - COLUMNS;
        }
        fb_write_cell(fb_currentCell++,buffer[i], fb_foreground, fb_background);
    }
    fb_move_cursor(fb_currentCell);
}