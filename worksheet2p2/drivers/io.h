#ifndef INCLUDE_IO_H
#define INCLUDE_IO_H

/**
 * outb:
 * Sends the given data to the specified I/O port.
 * Defined in io.asm.
 *
 * @param port The I/O port to send the data to.
 * @param data The data to send to the I/O port.
 */
void outb(unsigned short port, unsigned char data);

/**
 * inb:
 * Reads a byte from the specified I/O port.
 * Defined in io.asm.
 *
 * @param port The I/O port to read from.
 * @return The byte read from the I/O port.
 */
unsigned char inb(unsigned short port);

#endif /* INCLUDE_IO_H */
