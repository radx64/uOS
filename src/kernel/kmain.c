#include <stdint.h>
#include <stdio.h>
#include "gdt.h"
#include "idt.h"
#include "drivers/io.h"
#include "drivers/keyboard.h"
#include "drivers/vga.h"
#include "drivers/serial.h"
#include "apps/terminal.h"

#include "multiboot.h"

void headerPrint();

extern void keyboard_handler();

extern void enable_interrupts();

void kmain(multiboot_info_t* mbt, unsigned int magic)
{
    /**
    TODO: Initializing serial console before gdt and idt initalization
    is risky. Some hardware exception might happen that will lead to
    unhandled interrupt and (eventually) to processor triple fault.
    Serial writing is now only for some initial debugging. Some system
    for logging need to be implemented later on.
    */

    serial_init(SERIAL_COM1_BASE);
    serial_write("Serial initialization....[OK]\r\n");

    gdt_init();
    idt_init(&keyboard_handler);
    serial_write("Interrupts initalization....");
    enable_interrupts();
    serial_write("[OK]\r\n");
    terminal_init();
    kb_init(&terminal_on_keyboard_press);

    vga_clear();
    headerPrint();
    vga_set_colors(C_WHITE, C_BLACK);

    vga_write("Hello World from ");
    vga_set_colors(C_RED, C_BLACK);
    vga_write("KERNEL");
    vga_set_colors(C_WHITE, C_BLACK);
    vga_write("!\n\n");

    printf("GRUB magic: %p\n\n",magic);
    printf("%dkB (lower) / %dkB (upper) memory available \n", mbt->mem_lower, mbt->mem_upper);

    asm volatile ("int $0x3");
    asm volatile ("int $0x4");
}

void headerPrint()
{
    vga_set_colors(C_BLACK, C_LIGHT_GREEN);
    vga_write("\xc9");
    for (uint8_t i = 0; i< 50; ++i) vga_write("\xcd");
    vga_write("\xbb\n\xba");
    vga_write(" \xe6OS by radx64 was built on: " __DATE__ " " __TIME__ " ");
    vga_write("\xba\n\xc8");
    for (uint8_t i = 0; i< 50; ++i) vga_write("\xcd");
    vga_write("\xbc\n\n");
}