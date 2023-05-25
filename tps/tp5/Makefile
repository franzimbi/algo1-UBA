PROGRAM=Zimbimbakis_ej5
CC=gcc
CFLAGS=-Wall -Werror -std=c99 -pedantic -g
LDLIBS=-lm


all: $(PROGRAM)

$(PROGRAM): pixel.o imagen.o endianess.o main.o
	$(CC) $(CFLAGS) pixel.o imagen.o endianess.o main.o -o $(PROGRAM) $(LDLIBS)

pixel.o: pixel.c pixel.h
	$(CC) $(CFLAGS) -c pixel.c

imagen.o: imagen.c imagen.h pixel.h
	$(CC) $(CFLAGS) -c imagen.c

endianess.o: endianess.c endianess.h
	$(CC) $(CFLAGS) -c endianess.c

main.o: pixel.c pixel.h imagen.c imagen.h endianess.c endianess.h main.c
	$(CC) $(CFLAGS) -c main.c

clean: rm -vf *.o $(PROGRAM)

