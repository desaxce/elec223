#include "leds.h" 

// Initialize leds C1, C2, C3 anc E5 to output mode
void leds_init() {
	PCONC = PCONC & ~((1<<7)+(1<<5)+(1<<3));
	PCONC = PCONC | ((1<<2)+(1<<4)+(1<<6));

	PCONE = PCONE & ~(1<<11);
	PCONE = PCONE | (1<<10);
}

// Lights the C#number led
void leds_light_c(int16_t led_number) {
	PDATC = PDATC | (1 << led_number);
}

// Shades the C#number led
void leds_shade_c(int16_t led_number) {
	PDATC = PDATC & ~((1 << led_number));	
}

// Lights the E#number led
void leds_light_e(int16_t led_number) {
	PDATE = PDATE | (1 << led_number);
}

// Shades the E#number led
void leds_shade_e(int16_t led_number) {
	PDATE = PDATE & ~((1 << led_number));
}


