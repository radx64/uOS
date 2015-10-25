#include <stdint.h>
#include "drivers/io.h"
#include "drivers/vga.h"
#include "drivers/serial.h"

void sleep(uint32_t cycles)
{
    for(uint32_t j = 0; j < cycles; ++j)
    {
        __asm__("nop;");
    } // hot loop to see screen scrolling (need to implement timers support)    
}

void kmain()
{
    serial_init(SERIAL_COM1_BASE);
    serial_write("Serial initialized\r\n");

    vga_clear();
    vga_set_colors(C_BLACK, C_GREEN);
    vga_write("uOS by radx64 was built on: "
                __DATE__
                " "
                __TIME__
                "\n\n\n");
    sleep(10000000);
    vga_set_colors(C_WHITE, C_BLACK);

    vga_write("This is quite long string and it should be wrapped around to next line by VGA driver. Blah blah blah...\n");
    sleep(10000000);
    
    vga_write("\n\n\n ");
    for (int i = 1; i<256; ++i)
    {
        char c[]= " "; 
        c[0] = i; 
        vga_set_colors((i % 15) + 1, C_BLACK);
        switch (i)
        {
            case 0 :
            case 8 :
            case 9 :
            case 10 : vga_write("_"); break;
            default : vga_write(c);
        };
        if (i % 32 == 0) vga_write("\n");
    }


    while(1)
    {
        sleep(200000);
    };
}