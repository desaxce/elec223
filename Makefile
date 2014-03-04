CC=arm-none-eabi-gcc
LD=arm-none-eabi-ld
AS=arm-none-eabi-as
GDB=arm-none-eabi-gdb
OBJDUMP=arm-none-eabi-objdump
OBJCOPY=arm-none-eabi-objcopy

CFLAGS=-g -O1 -nostartfiles -std=gnu99 -Wall -Wextra -Werror
LINKER_SCRIPT=script.ld
LINKER_SCRIPT_CHENILLARD=script_chenillard.ld
LFLAGS=-nostartfiles

all: main main.lst main.bin chenillard.bin chenillard.lst

%.c: %.h
main.c: serial.h hello.h leds.h timers.h sound.h bootloader.h
hello.c: serial.h
bootloader.c: serial.h leds.h bootloader.h

chenillard: chenillard.o leds.o timers.o
	$(LD) $(LFLAGS) -T $(LINKER_SCRIPT_CHENILLARD) -o $@ $^

main: main.o hello.o serial.o leds.o timers.o sound.o bootloader.o crt0.o chenillard.o
	$(LD) $(LFLAGS) -T $(LINKER_SCRIPT) -o $@ $^

crt0.o: crt0.s
	$(AS) -o $@ $^

%.lst: %
	$(OBJDUMP) -D $^ > $@

gdb: main main.lst main.bin
	$(GDB) $<

%.bin: %
	$(OBJCOPY) -O binary $^ $@

.PHONY: clean

clean:
	rm -rf main
	rm -rf chenillard
	rm -rf *.bin
	rm -rf *.o
	rm -rf *.lst
