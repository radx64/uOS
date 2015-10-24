#include "drivers/io.h"

#ifndef SERIAL_H
#define SERIAL_H

#define SERIAL_COM1_BASE                0x3F8

#define SERIAL_DATA_PORT(base)          (base)
#define SERIAL_FIFO_COMMAND_PORT(base)  (base + 0x2)
#define SERIAL_LINE_COMMAND_PORT(base)  (base + 0x3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 0x4)
#define SERIAL_MODEM_STATUS_PORT(base)  (base + 0x5)

#define SERIAL_LINE_ENABLE_DLAB         0x80

void serial_configure_baud_rate(unsigned short com, unsigned short divisor);

void serial_configure_line(unsigned short com);

void serial_configure_buffers(unsigned short com);

int serial_is_transmit_fifo_empty(unsigned int com);

void serial_init(unsigned int com);

void serial_write(char* buffer, unsigned int length);

#endif // SERIAL_H