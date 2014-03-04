EXEC=main
SRC= $(subst l.c,,$(wildcard *.c))
OBJ= $(SRC:.c=.o)

$(EXEC): $(OBJ) 

%.c: main.h

.PHONY: clean

clean: 
	rm -rf *.o
	rm -rf $(EXEC)
