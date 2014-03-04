#include <stdint.h>

#define UTRSTAT0 	(*(volatile uint32_t *)	0x01D00010) // status register
#define UTXH0 		(*(volatile uint32_t *) 0x01D00020) // bits to send
#define URXH0 		(*(volatile uint32_t *)	0x01D00024) // bits to receive
#define ULCON0 		(*(volatile uint32_t *)	0x01D00000) // serial port conf
#define UCON0 		(*(volatile uint32_t *)	0x01D00004) // tx/rx mode
#define UFCON0		(*(volatile uint32_t *) 0x01D00008) // fifo control
#define UBRDIV0 	(*(volatile uint32_t *)	0x01D00028) // speed tx/rx

// Serial port initialization
void serial_init(uint32_t ulcon0, uint32_t ucon0, uint32_t ubrdiv0, uint32_t ufcon0);

// Send a character
void serial_putc(int8_t c);

// Get a character
int8_t serial_getc();

// Get a character
int8_t serial_getc_cond();

// Send a string
void serial_puts(int8_t *s);


