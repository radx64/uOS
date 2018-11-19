#include <stdint.h>
#include <stdio.h>

#include "drivers/io.h"
#include "drivers/serial.h"

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

static void (*keyboard_delegate)(uint8_t) = 0;

void keyboard_handler_main(void)
{
    unsigned char status;
    char keycode;

        /* write EOI */
        outb(0x20, 0x20);

        status = inb(KEYBOARD_STATUS_PORT);
        /* Lowest bit of status will be set if buffer is not empty */
        if (status & 0x01) {
            keycode = inb(KEYBOARD_DATA_PORT);
            if(keycode < 0)
                return;
            keyboard_delegate(keycode);
        }

}

void kb_init(void(*handler)(const uint8_t))
{
    serial_write("kb_init....");
    keyboard_delegate = handler;
    /* 0xFD is 11111101 - enables only IRQ1 (keyboard)*/
    outb(0x21 , 0xFD);
    serial_write("[ OK ]\r\n");
}



