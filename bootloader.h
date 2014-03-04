#include <stdint.h>
#include "serial.h"
#include "timers.h"

int bootloader();

int store(int8_t* input);
void transmit(int8_t* input);
void display(int8_t* input);
void new_line();
int8_t character_to_number(int8_t c);
int8_t number_to_character(int8_t c);
void integer_to_argument(uint32_t);
uint32_t argument_to_integer(int8_t*);

void write(uint32_t addr, uint32_t word);


