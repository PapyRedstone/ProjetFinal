SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

CFLAGS = -g -Wall -pedantic  
LDFLAGS = -lSDL -lSDL_image -lSDL_gfx
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
	/usr/bin/sudo /usr/bin/apt install libsdl1.2-dev libsdl-gfx1.2* libsdl-image1.2*

gdb:
	/usr/bin/gdb a.out
	
valgrind:
	/usr/bin/valgrind ./a.out appart.txt

run:
	./a.out appart.txt

remake: clean all
