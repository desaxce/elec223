#include "main.h"

// Main function
int main() {
	//hello();
    	//chenillard();
	//bip((uint16_t) 100);
	bootloader();
    	return 0;
}

/*// Chenillard function using leds
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
}*/

// Bip function for time milli-seconds
void bip(uint16_t time) {
	sound_start_bip();
	timers_pause(time);
	sound_end_bip();
}

