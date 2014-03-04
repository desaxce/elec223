#include "timers.h"

void timers_init() {

	// Configuration: prescaler=255; divider=32
	// Timer with period 125 us
	// One shot, manual update off, timer 2 stopped
	TCFG0 = TCFG0 & ~(0x0000ff00);
	TCFG0 = TCFG0 | (0x0000ff00);  
	TCFG1 = TCFG1 & ~(0x00000f00);
	TCFG1 = TCFG1 | 0x00000400;
	TCON = TCON & ~(0x0000f000);
	TCON = TCON | (0x00000000);
}

void timers_load_buffers(uint16_t time) {
	
	// Load values in down-counter buffers (time is in ms)
	TCNTB2 = TCNTB2 & ~(0xffff);
	TCNTB2 = TCNTB2 | (4*time);
	TCMPB2 = TCMPB2 & ~(0xffff);
}

void timers_start() {
	
	// Manual update on: load buffer values in registers
	// Start timer 2
	TCON = TCON | (1 << 13);
	TCON = TCON & ~(1 << 13);
	TCON = TCON | (1 << 12);
}

// Pauses time in milliseconds
void timers_pause(uint16_t time) {
	
	timers_init();

	timers_load_buffers(time);
	
	timers_start();

	// Wait
	while (TCNTO2==0);
	while (TCNTO2!=0) {}
}


