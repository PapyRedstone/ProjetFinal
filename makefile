SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

CFLAGS = -g -Wall -pedantic

all: a.out

a.out : $(OBJ)
	gcc -o $@ $^

%.o: %.c
	gcc -o $@ -c $< $(CFLAGS)

clean:
	rm *.o *.out *.gch -f

remake: clean all
