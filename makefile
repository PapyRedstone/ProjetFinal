SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

CFLAGS = -g -Wall -pedantic  
LDFLAGS = -lSDL -lSDL_image -lSDL_gfx -lm -lpython2.7 

all: a.out

a.out : $(OBJ)
	gcc -o $@ $^ $(LDFLAGS) 

%.o: %.c
	gcc -o $@ -c $< $(CFLAGS)

clean:
	rm *.o *.out *.gch -f

install:
	sudo apt install cython python3-dev python-dev

remake: clean all
