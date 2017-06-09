SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

CFLAGS = -g -Wall -pedantic  
LDFLAGS = -lSDL -lSDL_image -lSDL_gfx -lm -lpython2.7 
PATH:=$(shell pwd)

all: a.out

a.out : $(OBJ)
	gcc -o $@ $^ $(LDFLAGS) 

%.o: %.c
	gcc -o $@ -c $< $(CFLAGS)

clean:
	rm *.o *.out *.gch -f

install:
	/usr/bin/sudo /usr/bin/apt install cython python3-dev python-dev
	export PYTHONPATH='$(PATH)'

remake: clean all
