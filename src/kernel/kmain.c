#include "drivers/io.h"
#include "drivers/framebuffer.h"

void kmain()
{
    fb_clear();

    #define LONGTEXT 91
    char longtext[LONGTEXT] = "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890\n";
    write(longtext, LONGTEXT);
    #define LENGTH 23
    char hello[LENGTH] = "Hello world from uOS! \n";
    int i = 0;
    while(1)
    {
        fb_set_colors(i % 16, C_BLACK);
        write(hello, LENGTH);
        i++;
        for(int j=0;j<100000;++j){} // hot loop to see screen scrolling (need to implement timers support)
    };
};