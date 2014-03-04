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

all: controle controle.lst

%.elf: %.bin
	$(OBJCOPY) -I binary -O elf32-littlearm -B armv4t $^ $@

controle.c: controle.h

controle: controle.o crt0.o sound.elf
	$(LD) $(LFLAGS) -T $(LINKER_SCRIPT) -o $@ $^

crt0.o: crt0.s
	$(AS) -o $@ $^

%.lst: %
	$(OBJDUMP) -D $^ > $@

gdb: controle controle.lst 
	$(GDB) $<

.PHONY: clean

clean:
	rm -rf controle
	rm -rf *.o
	rm -rf *.lst
	rm -rf *.elf
