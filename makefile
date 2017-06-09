SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

CFLAGS = -g -Wall -pedantic  
LDFLAGS = -lSDL -lSDL_image -lSDL_gfx -I/usr/include/python2.7 -I/usr/include/python2.7 -lpthread -ldl -lutil -lm -lpython2.7 -Xlinker -export-dynamic


all: a.out

a.out : $(OBJ)
	gcc -o $@ $^ $(LDFLAGS) 

%.o: %.c
	gcc -o $@ -c $< $(CFLAGS)

clean:
	rm *.o *.out *.gch -f

remake: clean all
