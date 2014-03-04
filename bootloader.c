#include "bootloader.h"

extern void branch(uint32_t);
extern uint32_t _available_start;
extern uint32_t _available_end;

int bootloader() {
	//0x3 : 8 bits, no parity, 1 stop bit (same configuration as minicom)
	//0x5 : IRQ or polling mode for both transmission and reception
	//0x23: speed settings on the serial port (115200 & proc. 66MHz) 
	//0x31: activate the fifo mode and set receive buffer to 16 bytes

	serial_init(0x3, 0x5, 0x23, 0x31);
	new_line();		// Nice displaying
	
	int8_t input[50];	// this string stores the command typed in minicom
	int8_t char_buffer;
	int i = 0;
	int j = 0;

	timers_init();
	timers_load_buffers((uint16_t) 10000);
	timers_start();

	while (TCNTO2==0);
	while (TCNTO2!=0) {
		char_buffer = serial_getc_cond();
		if (TCNTO2==0) {
			goto fin;
		}
		if ((char_buffer != 0x0d) && (i < 50) && (char_buffer != 0x08) && (char_buffer != 0x1b)) {
			serial_putc(char_buffer);
			input[i] = char_buffer;
			i++;
		}
		else if ((char_buffer == 0x08) && (i!=0)) {			// If [DEL] is pressed, correct previous letter
			serial_putc((int8_t) 0x08);
			serial_putc((int8_t) 0x20);
			serial_putc((int8_t) 0x1b);
			serial_putc((int8_t) 0x5b);
			serial_putc((int8_t) 0x44);
			i--;
			input[i] = '\0';
		}
		else if (char_buffer == 0x0d) {			// If [ENTER] is pressed
			input[i] = '\0';			// first end the string
			serial_putc((int8_t) 0x0d);
			serial_putc((int8_t) 0x0a);
			//serial_puts((int8_t *) input);
			
			if ((input[0]==0x4c) && (input[1]==0x20)) {
				store((int8_t *) input);
			}
			else if ((input[0]==0x47) && (input[1]==0x20)) {
				transmit((int8_t *) input);
			}
			else if ((input[0]==0x52) && (input[1]==0x20)) {
				display((int8_t *) input);
			}
			else if ((input[0]==0x65) && (input[1]==0x78) && (input[2]==0x69) && (input[3]==0x74) && (input[4]=='\0')) { // exit function
				goto fin;			
			}
			else if ((input[0]==0x63) && (input[1]==0x6c) && (input[2]==0x65) && (input[3]==0x61) && (input[4]==0x72) && (input[5]=='\0')) { 
				serial_puts((int8_t *) "TODO: clear the screen");		
			}
			else if ((input[0]=='d') && (input[1]=='u') && (input[2]=='m') && (input[3]=='p')) { // dump function (useless)
				serial_puts((int8_t *) input);
			}
			else {
				serial_putc((int8_t) '\t' );
				serial_puts((int8_t *) "Unknown command.");
			}

			i = 0;
			new_line();
			for (j=0; j < 50; j++) {
				input[i] = '\0';
			}
		}
		else {
//			i = 0;
		}

		timers_init();
		timers_load_buffers((uint16_t) 10000);
		timers_start();

	}

	fin:
	branch((uint32_t) 0x3000);
		
	return 0;

}


void new_line() {
	serial_puts((int8_t *) "\033[31m"); 		// Got to launch minicom with '-c on' option if you want color
	serial_putc((int8_t) 0x0a);
	serial_putc((int8_t) 0x0d);
	serial_putc((int8_t) 0x3e);
	serial_putc((int8_t) 0x20); 
	serial_puts((int8_t *) "\033[0m");
}

// This function writes the word "word" at the address "addr"
void write(uint32_t addr, uint32_t word) {
	*((uint32_t *) addr) = word;
}

int store(int8_t* input) {
	serial_puts((int8_t *) "\033[32mStore function\033[0m");
	
	uint32_t addr = argument_to_integer((int8_t *) (input+4)); // input+4 is start of the address
	if (addr >= _available_start && addr <= _available_end) {

		timers_init();
		timers_load_buffers((uint16_t) 5000);
		timers_start();

		while (TCNTO2==0);
		//int compteur = 0;
		//uint32_t word = 0;
		int8_t c;
		uint8_t *addr_to_write = (uint8_t *) addr;

		while (TCNTO2!=0) {
			c = serial_getc_cond();
			if (TCNTO2==0) {
				goto end;
			}

			*addr_to_write++ = (uint8_t) c;

			/*if (compteur < 3) {
				word += ((uint8_t) c) <<((compteur)*8);
				compteur++;
			}
			else if (compteur==3) {
				word += ((uint8_t) c) <<(compteur*8);
				*addr_to_write++ = word;
				//write(addr_to_write, word);
				//addr_to_write += 4;
				word = 0;
				compteur = 0;
			}*/
			timers_init();
			timers_load_buffers((uint16_t) 5000);
			timers_start();


		}
	}
	/*else {
		serial_puts((int8_t *) "Address out of bounds, cannot write there");
	}*/
	end:
	return 0;
}

void transmit(int8_t* input) {
	serial_puts((int8_t *) "\033[32mTransmit function\033[0m");
	uint32_t addr = argument_to_integer((int8_t *) (input+4)); // input+4 is start of the address
	branch(addr);
}

// Displays content of memory at input
void display(int8_t* input) {
	serial_puts((int8_t *) "\033[32mDisplay function : \033[0m");
	serial_puts((int8_t *) "@(");
	serial_puts((int8_t *) (input+2));
	serial_puts((int8_t *) ") = 0x");

	uint32_t addr = argument_to_integer((int8_t *) (input+4)); // input+4 is start of the address
	uint32_t output = *((uint32_t *) addr);
	integer_to_argument(output);
}

// Converts a numerical value (uint32_t) to a string (address)
void integer_to_argument(uint32_t address) {
	int i = 0;
	int8_t resultat[8];
	for (i = 0; i < 8; i++) {
		resultat[i] = number_to_character((int8_t) ((address & ((0xf) << ((7-i)*4))) >> ((7-i)*4)));
	}
	resultat[8] = 0;
	serial_puts((int8_t *) resultat);
}

// Converts a string to a numerical value (we assume addr has length 8)
uint32_t argument_to_integer(int8_t* addr) {
	uint32_t result = (uint32_t) (character_to_number(addr[0]) << 7*4);
	int i = 0;
	for (i = 1; i < 8; i++) {
		result += (uint32_t) (character_to_number(addr[i]) <<((7-i)*4));
	}
	return result;

}

// Converts a character (like 'a' = 0x41) into its numerical value (0xa=10)
int8_t character_to_number(int8_t c) {
	switch (c) {
		case 0x61:
			return (int8_t) 0xa;
			break;
		case 0x62:
			return (int8_t) 0xb;
			break;
		case 0x63:
			return (int8_t) 0xc;
			break;
		case 0x64:
			return (int8_t) 0xd;
			break;
		case 0x65:
			return (int8_t) 0xe;
			break;
		case 0x66:
			return (int8_t) 0xf;
			break;
		case 0x41:
			return (int8_t) 0xa;
			break;
		case 0x42:
			return (int8_t) 0xb;
			break;
		case 0x43:
			return (int8_t) 0xc;
			break;
		case 0x44:
			return (int8_t) 0xd;
			break;
		case 0x45:
			return (int8_t) 0xe;
			break;
		case 0x46:
			return (int8_t) 0xf;
			break;
		case 0x30:
			return (int8_t) 0x0;
			break;
		case 0x31:
			return (int8_t) 0x1;
			break;
		case 0x32:
			return (int8_t) 0x2;
			break;
		case 0x33:
			return (int8_t) 0x3;
			break;
		case 0x34:
			return (int8_t) 0x4;
			break;
		case 0x35:
			return (int8_t) 0x5;
			break;
		case 0x36:
			return (int8_t) 0x6;
			break;
		case 0x37:
			return (int8_t) 0x7;
			break;
		case 0x38:
			return (int8_t) 0x8;
			break;
		case 0x39:
			return (int8_t) 0x9;
			break;
	}
	return (int8_t) 0;
}

// Converts a numerical valule (like 0) into its character representation (0x30) 
int8_t number_to_character(int8_t c) {
	switch(c) {
		case 0x0:
			return (int8_t) 0x30;
			break;
		case 0x1:
			return (int8_t) 0x31;
			break;
		case 0x2:
			return (int8_t) 0x32;
			break;
		case 0x3:
			return (int8_t) 0x33;
			break;
		case 0x4:
			return (int8_t) 0x34;
			break;
		case 0x5:
			return (int8_t) 0x35;
			break;
		case 0x6:
			return (int8_t) 0x36;
			break;
		case 0x7:
			return (int8_t) 0x37;
			break;
		case 0x8:
			return (int8_t) 0x38;
			break;
		case 0x9:
			return (int8_t) 0x39;
			break;
		case 0xa:
			return (int8_t) 0x41;
			break;
		case 0xb:
			return (int8_t) 0x42;
			break;
		case 0xc:
			return (int8_t) 0x43;
			break;
		case 0xd:
			return (int8_t) 0x44;
			break;
		case 0xe:
			return (int8_t) 0x45;
			break;
		case 0xf:
			return (int8_t) 0x46;
			break;
	}
	return (int8_t) 0x30;
}


