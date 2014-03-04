OPT=-O1

OPTIONS=-Wall -Wextra $(OPT) -g 

all: test.o

%.o: %.c
	arm-none-eabi-gcc $(OPTIONS) -c $^ -o $@

.PHONY: clean

clean:
	rm -rf *.o
	rm -rf test
