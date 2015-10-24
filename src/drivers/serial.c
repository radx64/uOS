#include "drivers/serial.h"

void serial_configure_baud_rate(unsigned short com, unsigned short divisor)
{
    outb(SERIAL_LINE_COMMAND_PORT(com),SERIAL_LINE_ENABLE_DLAB);
    outb(SERIAL_DATA_PORT(com), (divisor >> 8) & 0x00FF);
    outb(SERIAL_DATA_PORT(com), divisor & 0x00FF);
}

void serial_configure_line(unsigned short com)
{
    outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}

void serial_configure_buffers(unsigned short com)
{
    outb(SERIAL_FIFO_COMMAND_PORT(com), 0xC7);
}

void serial_configure_modem(unsigned short com)
{
    outb(SERIAL_MODEM_COMMAND_PORT(com), 0x03);
}

int serial_is_transmit_fifo_empty(unsigned int com)
{
    return inb(SERIAL_MODEM_STATUS_PORT(com)) & 0x20;
}

void serial_write(char* buffer, unsigned int length)
{
    for (unsigned int i=0;i<length;++i)
    {
        while(!serial_is_transmit_fifo_empty(SERIAL_COM1_BASE)){}
        outb(SERIAL_COM1_BASE, buffer[i]);
    }
}