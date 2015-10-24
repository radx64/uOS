#ifndef IO_H
#define IO_H

/** inb:
*   Read a byte from an I/O port
*
*   @param port The address of the I/O port
*   @return     The read byte
*/

unsigned char inb(unsigned short port);

/** outb:
*   Write a byte to an I/O port
*
*   @param port The address of the I/O port
*   @param data The byte to write
*/
void outb(unsigned short port, unsigned char data);

#endif // IO_H