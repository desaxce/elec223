#include "controle.h"

extern uint32_t _binary_sound_bin_start;
extern uint32_t _binary_sound_bin_end;
extern uint32_t _binary_sound_bin_size;

const int16_t samples[72] = {32512 ,  32388 ,  32018 ,  31404 ,
                       30551 ,  29465 ,  28156 ,  26632 ,
                       24905 ,  22989 ,  20898 ,  18648 ,
                       16256 ,  13740 ,  11119 ,  8414 ,
                       5645 ,  2833 ,  0 ,  -2833 ,
                       -5645 ,  -8414 ,  -11119 ,  -13740 ,
                       -16255 ,  -18648 ,  -20898 ,  -22989 ,
                       -24905 ,  -26632 ,  -28156 ,  -29465 ,
                       -30551 ,  -31404 ,  -32018 ,  -32388 ,
                       -32512 ,  -32388 ,  -32018 ,  -31404 ,
                       -30551 ,  -29465 ,  -28156 ,  -26632 ,
                       -24905 ,  -22989 ,  -20898 ,  -18648 ,
                       -16256 ,  -13740 ,  -11119 ,  -8414 ,
                       -5645 ,  -2833 ,  0 ,  2833 ,
                       5645 ,  8414 ,  11119 ,  13740 ,
                       16255 ,  18648 ,  20898 ,  22989 ,
                       24905 ,  26632 ,  28156 ,  29465 ,
                       30551 ,  31404 ,  32018 ,  32388 };
int main() {
	i2s_init();
	//test_tone();
	send_stereo_sound();
	return 0;

}

void test_tone() {
	int i = 0;
	int32_t tmp = 0;
	while (1) {
		for (i=0; i < 36; i++) {
			tmp = samples[2*i]+(samples[2*i+1]<<16);
			send_stereo_sample(tmp);
		}
	}
}

void i2s_init(void) {
	//IISFCON = IISFCON | ((1<<8)+(1<<9));
	IISFCON = 0x200;
	IISCON = 0x3;
	//IISCON = IISCON | (1<<);
	IISMOD = 0x89;
	IISPSR = 0x33;
}

void send_word_to_fifo(int16_t word) {
	while (((IISFCON & ((0xf)<<4))>>4)>=8); // While fifo full
	IISFIF = word;
}

void send_stereo_sample(int32_t sample) {
	send_word_to_fifo((int16_t) (sample & 0xffff));
	send_word_to_fifo((int16_t) ((sample & (0xffff<<16))>>16));
}

void send_stereo_sound() { 
	uint32_t addr = 0x0c001000;
	while (1) {
		addr = 0x0c001000;
		while (addr < 0x0c001000 + _binary_sound_bin_size) {
			send_stereo_sample( *((int32_t *) addr ) );
			addr += 4;
		}
	}
}

