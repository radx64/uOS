#include <stdint.h>
#include <stdio.h>
#include "gdt.h"
#include "idt.h"
#include "drivers/io.h"
#include "drivers/keyboard.h"
#include "drivers/vga.h"
#include "drivers/serial.h"
#include "apps/terminal.h"

void headerPrint();

extern void keyboard_handler();

void kmain()
{
    serial_init(SERIAL_COM1_BASE);
    serial_write("Serial initialized\r\n");
    gdt_init();
    idt_init(&keyboard_handler);
    kb_init(&on_keyboard_press);

    vga_clear();
    headerPrint();
    vga_set_colors(C_WHITE, C_BLACK);

    vga_write("Hello World from ");
    vga_set_colors(C_RED, C_BLACK);
    vga_write("KERNEL");
    vga_set_colors(C_WHITE, C_BLACK);
    vga_write("!\n");
}

void headerPrint()
{
    vga_set_colors(C_BLACK, C_GREEN);
    char micro[]  = " ";
    micro[0] = 230;
    vga_write(micro);
    vga_write(
        "OS by radx64 was built on: "
                __DATE__
                " "
                __TIME__
                "\n\n");    
}