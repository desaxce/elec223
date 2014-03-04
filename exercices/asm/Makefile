all: exo1.o exo2.o exo3.o exo4_1.o exo4_2.o exo5.o

%.o: %.s
	arm-none-eabi-as -g -o $@ $^

.PHONY: clean

clean:
	rm -rf *.o


