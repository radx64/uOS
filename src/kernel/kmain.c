#include "drivers/io.h"
#include "drivers/vga.h"
#include "drivers/serial.h"

void kmain()
{
    vga_clear();
    serial_configure_baud_rate(SERIAL_COM1_BASE, 0x1);
    serial_configure_line(SERIAL_COM1_BASE);
    serial_configure_buffers(SERIAL_COM1_BASE);

    #define LONGTEXT 91
    char longtext[LONGTEXT] = "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890\n";
    vga_write(longtext, LONGTEXT);
    #define LENGTH 41
    char hello[LENGTH] = "Hello world from uOS!\t\tNow with tabs!\t\t\2\n";
    int i = 0;
    while(1)
    {
        vga_set_colors(i % 16, C_BLACK);
        vga_write(hello, LENGTH);
        serial_write(hello, LENGTH);
        i++;
        for(int j=0;j<100000;++j){} // hot loop to see screen scrolling (need to implement timers support)
    };
};