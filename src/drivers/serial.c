#include "drivers/serial.h"

void serial_configure_baud_rate(unsigned short com, unsigned short divisor)
{
    outb(SERIAL_LINE_COMMAND_PORT(com),SERIAL_LINE_ENABLE_DLAB);
    outb(SERIAL_DATA_PORT(com), (divisor >> 8) & 0x00FF);
    outb(SERIAL_DATA_PORT(com), divisor & 0x00FF);
}

void serial_configure_line(unsigned short com)
{
    /*
    Bit:      | 7 | 6 | 5 4 3 | 2 | 1 0 |
    Content:  | d | b | parity| s | dl  |
    Value:    | 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x3

    d      - Enables (d = 1) or disables (d = 0) DLAB
    b      - Break control is enabled (b = 1) or disabled (b = 0)
    parity - Number of parity bits tu use
    s      - The number of stop bits to use (s = 0 equals 1, s = 1 eguals 1.5 or 2)
    dl     - Describe length od data
    */

    outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}

void serial_configure_buffers(unsigned short com)
{
    /*
    Bit:      | 7 6 | 5 | 4 | 3 | 2 | 1 | 0 |
    Content:  | lvl | bs| r |dma|clt|clr| e |
    Value:    | 1 1 | 0 | 0 | 0 | 1 | 1 | 1 | = 0xC7
    
    lvl - How many bytes should be stored in the FIFO buffers
    bs  - Buffer size (bs = 0 -> 16 or bs = 0 -> 64 bytes)
    r   - Reserved
    dma - How serial port should be accessed
    clt - Clear the transmission FIFO buffer
    clr - Clear the receiver FIFO buffer
    e   - Should the FIFO buffer would be enabled (e = 1) or not (e = 0)
    */

    outb(SERIAL_FIFO_COMMAND_PORT(com), 0xC7);
}

void serial_configure_modem(unsigned short com)
{
    /*
    Bit:      | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
    Content:  | r | r | af| lb|ao2|ao1|rts|dtr|
    Value:    | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 1 | = 0x3
    
    r   - Reserved
    af  - Auto flow control enabled
    lb  - Loopback mode (debbuging mode)
    ao2 - Auxiliary output 2 - for interrupts (not used for now)
    ao1 - Auxiliary output 1
    rts - Ready To Transmit
    dtr - Data Terminal Ready
    */

    outb(SERIAL_MODEM_COMMAND_PORT(com), 0x03);
}

int serial_is_transmit_fifo_empty(unsigned int com)
{
    
    /*
    Bit:      | 7 | 6 | 5 | 4 | 3  | 2  | 1  | 0  |
    Content:  |rls| ri|dsr|cts|crls|teri|cdsr|ccts|
    Value:    | 0 | 0 | 1 | 0 | 0  | 0  | 0  | 0  | = 0x20

    rls  - Received Line Signal Detected 
    ri   - Ring Indicator 
    dsr  - Data Set Ready 
    cts  - Clear to Send 
    crls - Change in RLSD
    teri - Trailing Edge RI
    cdsr - Change in DSR
    ccts - Change in CTS
    */
    
    return inb(SERIAL_MODEM_STATUS_PORT(com)) & 0x20;
}

void serial_init(unsigned int com)
{
    serial_configure_baud_rate(com, SERIAL_SPEED_115200);
    serial_configure_line(com);
    serial_configure_buffers(com);
}

void serial_write(char* buffer, unsigned int length)
{
    for (unsigned int i=0;i<length;++i)
    {
        while(!serial_is_transmit_fifo_empty(SERIAL_COM1_BASE)){}
        outb(SERIAL_COM1_BASE, buffer[i]);
    }
}