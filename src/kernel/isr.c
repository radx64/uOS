/*
    isr.c -- High level interrupt service routines and interrupt request handlers.
    Part of this code is modified from Bran's kernel development tutorials.
    Rewritten for JamesM's kernel development tutorials.
    Ported to uOS by radx64.
*/

#include <string.h>

#include "isr.h"
#include "drivers/serial.h"

/* This gets called from ASM interrupt handler stub. */
void isr_handler(registers_t regs)
{
    char interupt_number_text_buffer[5];
    char* result = itoa(regs.int_no, interupt_number_text_buffer+4, 10);

    serial_write("Recieved interrupt no: ");
    serial_write(result);
    serial_write("\r\n");
}
