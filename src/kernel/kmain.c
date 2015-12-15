#include <stdint.h>
#include <stdio.h>
#include "gdt.h"
#include "idt.h"
#include "drivers/io.h"
#include "drivers/vga.h"
#include "drivers/serial.h"

void sleep(uint32_t cycles);
void headerPrint();
void asciiDemo();
void printfDemo();

void kmain()
{
    //gdt_init();
    serial_init(SERIAL_COM1_BASE);
    serial_write("Serial initialized\r\n");

    idt_init();
    kb_init();

    vga_clear();
    headerPrint();
    sleep(1000000);
    vga_set_colors(C_WHITE, C_BLACK);

    vga_write("This is quite long string and it should be wrapped around to next line by VGA driver. Blah blah blah...\n");
    sleep(1000000);
    asciiDemo();
    sleep(1000000);
    printfDemo();
}

void sleep(uint32_t cycles)
{
    for(uint32_t j = 0; j < cycles; ++j)
    {
        __asm__ volatile("nop");
    }
}

void headerPrint()
{
    vga_set_colors(C_BLACK, C_GREEN);
    vga_write("uOS by radx64 was built on: "
                __DATE__
                " "
                __TIME__
                "\n\n");    
}

void asciiDemo()
{
    vga_write("\n\n");
    for (int i = 1; i<256; ++i)
    {
        char c[]= " "; 
        c[0] = i; 
        vga_set_colors((i % 15) + 1, C_BLACK);
        switch (i)
        {
            case 0 :    // skip ASCIZ zero
            case 9 :    // skip tabulator
            case 10 : vga_write("_"); break; // skip newline 
            default : vga_write(c);
        };
        if (i % 32 == 0) vga_write("\n");
    }    
}


void printfDemo()
{
    vga_write("\n\n");
    vga_set_colors(C_WHITE, C_BLACK);
    printf("This is printf without any additional params.\n");
    printf("This is printf with  %%s  support - %s\n", "this is a string as param");
    printf("This is printf with  %%d  support - %d\n", 1234);
    printf("This is printf with  %%d  support - %d\n", -1234);
    printf("This is printf with  %%p  support - %p\n", 0x1234);
    printf("This is printf with  %%c  support - %c\n", 'a');    
}