#include "hello.h"

// Hello function
void hello() {
	// 0x3 : 8 bits, no parity, 1 stop bit (same configuration as minicom)
	// 0x5 : IRQ or polling mode for both transmission and reception
	// 0x23: speed settings on the serial port (115200 & proc. 66MHz)
	// 0x31: activate the fifo mode and set receive buffer to 16 bytes
	serial_init(0x3, 0x5, 0x23, 0x31);
	serial_puts((int8_t *) "Hello World!\n");
}


