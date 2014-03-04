#include "sound.h"

void sound_start_do() {

}

void sound_start_re() {

}

void sound_start_mi() {

}

void sound_start_fa() {

}

void sound_start_sol() {

}

void sound_start_la() {

}

void sound_start_si() {

}

void sound_end_do() {

}

void sound_end_re() {

}

void sound_end_mi() {

}

void sound_end_fa() {

}

void sound_end_sol() {

}

void sound_end_la() {

}

void sound_end_si() {

}




// Bip sound
void sound_start_bip() {
	// Configuration E6 pin to TOUT3
	PCONE = PCONE & ~(1 << 12);
	PCONE = PCONE | (1 << 13);

	// Timer 3 configuration: prescaler=255; divider=16
	// Signal frequency = 14.6 kHz
	// Auto-reload on, manual update off, timer 3 stopped
	TCFG0 = TCFG0 & ~(0x0000ff00);
	TCFG0 = TCFG0 | (0x0000ff00);
	TCFG1 = TCFG1 & ~(0x0000f000);
	TCFG1 = TCFG1 | 0x00003000;
	TCON = TCON & ~(0x000f0000);
	TCON = TCON | (0x00080000);

	// Load timer buffers 
	TCNTB3 = TCNTB3 & ~(0xffff);
	TCNTB3 = TCNTB3 | (0x000e);	// e dans le TCNTB: on divise la freq 14.6 par 6
	TCMPB3 = TCMPB3 & ~(0xffff);
	TCMPB3 = TCMPB3 | (0x0001);

	// Load buffered values into registers
	// Manual update on/off
	// Start timer
	TCON = TCON | (1 << 17);
	TCON = TCON & ~(1 << 17);	
	TCON = TCON | (1 << 16);
}


void sound_end_bip() {
	// Unplug TOUT3 and E6 pin
	// Turn off timer
	PCONE = PCONE & ~(1 << 13);
	TCON = TCON & ~(1 << 16);
}
