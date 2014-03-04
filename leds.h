#include <stdint.h>

#define PCONC		(*(volatile uint32_t *)	0x01D20010) // Configures the pins of port C
#define PDATC	 	(*(volatile uint32_t *)	0x01D20014) // The data register for port C
#define PUPC	 	(*(volatile uint32_t *)	0x01D20018) // pull-up disable register for port C

#define PCONE		(*(volatile uint32_t *)	0x01D20028) // Configures the pins of port E
#define PDATE	 	(*(volatile uint32_t *)	0x01D2002c) // The data register for port E
#define PUPE	 	(*(volatile uint32_t *)	0x01D20030) // pull-up disable register for port E

// Initialize leds C1, C2, C3, E5
void leds_init();

// Light the C#num led
void leds_light_c(int16_t);

// Shades the C#num led
void leds_shade_c(int16_t);

// Light the E#num led
void leds_light_e(int16_t);

// Shades the E#num led
void leds_shade_e(int16_t);



