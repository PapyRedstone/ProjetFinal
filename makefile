SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

CFLAGS = -g -Wall -pedantic  
LDFLAGS = -lSDL -lSDL_image -lSDL_gfx -lm -lpython2.7 
PATH:=$(shell pwd)
AS:=$(shell which as)
GCC:=$(shell which gcc)
LD:=$(shell which ld)

all: a.out

a.out : $(OBJ)
	gcc -o $@ $^ $(LDFLAGS) 

%.o: %.c
	gcc -o $@ -c $< $(CFLAGS)

clean:
	/bin/rm *.o *.out *.gch -f

install:
	/bin/ln $(LD) ld -sf
	/bin/ln $(AS) as -sf
	/bin/ln $(GCC) gcc -sf
	/usr/bin/sudo /usr/bin/apt install cython cython3 python-dev python3-dev python-dev libsdl1.2-dev libsdl-gfx1.2* libsdl-image1.2*

gdb:
	export PYTHONPATH='$(PATH)'
	/usr/bin/gdb a.out
	
valgrind:
	export PYTHONPATH='$(PATH)'
	/usr/bin/valgrind ./a.out appart.txt

run:
	export PYTHONPATH='$(PATH)'
	./a.out appart.txt

remake: clean all
