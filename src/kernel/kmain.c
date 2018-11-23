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

/*
int main(multiboot_info* mbt, unsigned int magic) {
	...
	multiboot_memory_map_t* mmap = mbt->mmap_addr;
	while(mmap < mbt->mmap_addr + mbt->mmap_length) {
		...
		mmap = (multiboot_memory_map_t*) ( (unsigned int)mmap + mmap->size + sizeof(mmap->size) );
	}
	...
}
*/


void kmain(multiboot_info_t* mbt, unsigned int magic)
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

    printf("GRUB magic: %p\n",magic);

    multiboot_memory_map_t* mmap = (multiboot_memory_map_t*)mbt->mmap_addr;

    while((unsigned int)mmap < mbt->mmap_addr + mbt->mmap_length) 
    {
	printf("Size: %p\tAddr: %p\tLength: %p\tType: %p\n",mmap->size, mmap->addr, mmap->len, mmap->type);
        mmap = (multiboot_memory_map_t*) ( (unsigned int)mmap + mmap->size + sizeof(mmap->size) );

    }
}

void headerPrint()
{
    vga_set_colors(C_BLACK, C_RED);
    vga_write("\xc9");
    for (uint8_t i = 0; i< 50; ++i) vga_write("\xcd");
    vga_write("\xbb\n\xba");
    vga_write(" \xe6OS by radx64 was built on: " __DATE__ " " __TIME__ " ");
    vga_write("\xba\n\xc8");
    for (uint8_t i = 0; i< 50; ++i) vga_write("\xcd");
    vga_write("\xbc\n\n");
}