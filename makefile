SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

CFLAGS = -g -Wall -pedantic 
LDFLAGS = -lSDL -lSDL_image -lSDL_gfx

all: a.out

a.out : $(OBJ)
	gcc -o $@ $^ $(LDFLAGS)

%.o: %.c
	gcc -o $@ -c $< $(CFLAGS)

clean:
	rm *.o *.out *.gch -f

remake: clean all
