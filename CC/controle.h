#include <stdint.h>

#define IISFCON 	(*(volatile uint32_t *)	0x01D1800C)
#define IISCON		(*(volatile uint32_t *)	0x01D18000)
#define IISMOD	 	(*(volatile uint32_t *)	0x01D18004)
#define IISPSR	 	(*(volatile uint32_t *)	0x01D18008)
#define IISFIF	 	(*(volatile uint32_t *)	0x01D18010)

void i2s_init(void);
void send_word_to_fifo(int16_t word);
void send_stereo_sample(int32_t sample);
void send_stereo_sound();
void test_tone();

