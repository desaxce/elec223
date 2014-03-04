#include <stdint.h>

#define TCFG0		(*(volatile uint32_t *) 0x01D50000) //
#define TCFG1		(*(volatile uint32_t *) 0x01D50004) // Config reg for timers
#define TCON		(*(volatile uint32_t *) 0x01D50008) //

#define TCNTB0		(*(volatile uint16_t *) 0x01D5000C) //
#define TCMPB0		(*(volatile uint16_t *) 0x01D50010) // timer 0
#define TCNTO0		(*(volatile uint16_t *) 0x01D50014) //

#define TCNTB1		(*(volatile uint16_t *) 0x01D50018) //
#define TCMPB1		(*(volatile uint16_t *) 0x01D5001C) // timer 1
#define TCNTO1		(*(volatile uint16_t *) 0x01D50020) //

#define TCNTB2		(*(volatile uint16_t *) 0x01D50024) //
#define TCMPB2		(*(volatile uint16_t *) 0x01D50028) // timer 2
#define TCNTO2		(*(volatile uint16_t *) 0x01D5002C) //

#define TCNTB3		(*(volatile uint16_t *) 0x01D50030) //
#define TCMPB3		(*(volatile uint16_t *) 0x01D50034) // timer 3
#define TCNTO3		(*(volatile uint16_t *) 0x01D50038) //

#define TCNTB4		(*(volatile uint16_t *) 0x01D5003C) //
#define TCMPB4		(*(volatile uint16_t *) 0x01D50040) // timer 4
#define TCNTO4		(*(volatile uint16_t *) 0x01D50044) //

#define	TCNTB5		(*(volatile uint16_t *) 0x01D50048) // 
#define TCNTO5		(*(volatile uint16_t *) 0x01D5004C) // timer 5

// Pauses for 1s
void timers_pause(uint16_t time);

// Initialize timer
void timers_init();

// Load waiting time in buffers
void timers_load_buffers(uint16_t time);

// Start timer
void timers_start();

