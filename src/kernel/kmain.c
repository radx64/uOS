#include "drivers/io.h"
#include "drivers/vga.h"
#include "drivers/serial.h"

void kmain()
{
    vga_clear();
    serial_init(SERIAL_COM1_BASE);
    serial_write("Serial initialized\r\n", 20);

    #define LONGTEXT 92
    char longtext[] = "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890\n";
    vga_write(longtext);
    #define LENGTH 42
    char hello[] = "Hello world from uOS!\t\tNow with tabs!\t\t\2\n";
    int i = 0;
    while(1)
    {
        vga_set_colors(i % 16, C_BLACK);
        vga_write(hello);
        i++;
        for(int j=0;j<100000;++j){} // hot loop to see screen scrolling (need to implement timers support)
    };
};