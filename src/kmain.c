#include "io.h"
#include "framebuffer.h"

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