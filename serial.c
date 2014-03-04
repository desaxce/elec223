#include "serial.h"
#include "timers.h"

// Serial port initialization
void serial_init(uint32_t ulcon0, uint32_t ucon0, uint32_t ubrdiv0, uint32_t ufcon0) {
	ULCON0 = ulcon0;	// serial port configuration
	UCON0 = ucon0;		// tx/rx mode
	UBRDIV0 = ubrdiv0;	// serial port speed
	UFCON0 = ufcon0;	// fifo configuration
}

// Send a character
void serial_putc(int8_t c) {
	// First wait till the tx buffer be available		
	while (!(UTRSTAT0 & 0x2)) {}
	UTXH0 = c;
}

// Get a character
int8_t serial_getc() {
	while (!(UTRSTAT0 & 0x1)) {	// Check if buffer non empty
	}
	return URXH0;	// TODO: Corriger le type (parce que là on renvoit un uint32_t
}

// Get a character with condition on timer 2 -> better move this function to
// another file because it's annoying that serial functions depend on timers.h
int8_t serial_getc_cond() {
	while (!(UTRSTAT0 & 0x1) && TCNTO2!=0) {	// Check if buffer non empty
	}
	return URXH0;	// TODO: Corriger le type (parce que là on renvoit un uint32_t
}

// Send a string
void serial_puts(int8_t *s) {
	int i = 0;				// 'i' allows to check the stack works
	while (s[i] != '\0') {
		serial_putc(s[i]);		// TODO: Optimiser cette fonction sur une ligne
		++i;
	}
}


