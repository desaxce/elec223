#include "chenillard.h"

// Chenillard function using leds
void chenillard() {
	leds_init();
	int16_t num;
	while (1) {
		num = 1;
		for (num = 1; num < 4; num ++) {
			leds_light_c(num);
			timers_pause((uint16_t) 1000);
			leds_shade_c(num);
		}
		leds_light_e((int16_t) 5);
		timers_pause((uint16_t) 1000);
		leds_shade_e((int16_t) 5);
	}
}

