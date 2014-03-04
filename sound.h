#include <stdint.h>

#define TCFG0		(*(volatile uint32_t *) 0x01D50000) //
#define TCFG1		(*(volatile uint32_t *) 0x01D50004) // Config reg for timers
#define TCON		(*(volatile uint32_t *) 0x01D50008) //

#define PCONE		(*(volatile uint32_t *)	0x01D20028) // Configures the pins of port E
#define PDATE	 	(*(volatile uint32_t *)	0x01D2002c) // The data register for port E
#define PUPE	 	(*(volatile uint32_t *)	0x01D20030) // pull-up disable register for port E

#define TCNTB3		(*(volatile uint16_t *) 0x01D50030) //
#define TCMPB3		(*(volatile uint16_t *) 0x01D50034) // timer 3
#define TCNTO3		(*(volatile uint16_t *) 0x01D50038) //

// Starts a bip sound on E6
void sound_start_bip();

// Ends a bip sound on E6
void sound_end_bip();

void sound_start_do();
void sound_start_re();
void sound_start_mi();
void sound_start_fa();
void sound_start_sol();
void sound_start_la();
void sound_start_la();

void sound_end_do();
void sound_end_re();
void sound_end_mi();
void sound_end_fa();
void sound_end_sol();
void sound_end_la();
void sound_end_si();


