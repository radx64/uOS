/*
Framebuffer address: 0x000B8000
Framebuffer cell structure
Bit:        |15 14 13 12 11 10  9  8| 7  6  5  4  3  2  1  0|
Content:    |ASCII CODE OF CHARACTER|   FG      |     BG    |
*/

#include "io.h"

#define COLUMNS 80
#define ROWS 25
#define CELL_SIZE 2

char* fb = (char *) 0x000B8000;

void fb_write_cell(
    unsigned int location,
    char character,
    unsigned char foreground,
    unsigned char background)
{
    fb[location] = character;
    fb[location+1] = (foreground & 0x0F) | ((background * 0x0F)<< 4);
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

    unsigned int offset = (COLUMNS * y + x) * CELL_SIZE;
    fb_write_cell(offset, character, foreground, background);
}

void fb_clear()
{
    for(int offset = 0; offset <= COLUMNS*ROWS*CELL_SIZE; offset+=2)
    {
        fb[offset] = 0;    
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


void kmain()
{
    fb_clear();

    #define LENGTH 21
    unsigned char hello[LENGTH] = "Hello world from uOS!";

    for(unsigned char c = 0; c < LENGTH; ++c)
    {
        fb_write_at_location(c,0,hello[c],0xA,0x0);   
    }

    while(1)
    {
        for (unsigned int r = 0; r < ROWS; ++r)
        {
            for (unsigned int c = 0; c < COLUMNS; ++c)
            {
                fb_move_cursor(c, r);
                for(int i=0; i<500000; ++i){}    //hot loop cause no sleep implemented yet
            }
        }
    }

};