SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

CFLAGS = -g -Wall -pedantic -O3
LDFLAGS = -lSDL -lSDL_image

all: a.out

a.out : $(OBJ)
	gcc -o $@ $^ $(LDFLAGS)

%.o: %.c
	gcc -o $@ -c $< $(CFLAGS)

clean:
	rm *.o *.out *.gch -f

remake: clean all
