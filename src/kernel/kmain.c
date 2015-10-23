#include "drivers/io.h"
#include "drivers/framebuffer.h"

void kmain()
{
    fb_clear();

    #define LENGTH 23
    unsigned char hello[LENGTH] = "Hello world from uOS! \2";

    for(unsigned char c = 0; c < LENGTH; ++c)
    {
        fb_write_at_location(c+COLUMNS/2-LENGTH/2-1,ROWS/2-1,hello[c],(Color)(c%0xE)+1,C_BLACK);   
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