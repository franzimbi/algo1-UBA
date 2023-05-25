PROGRAM=Zimbimbakis_ej5
CC=gcc
CFLAGS=-Wall -Werror -std=c99 -pedantic -g
LDLIBS=-lm


all: $(PROGRAM)

$(PROGRAM): pixel.o imagen.o main.o filtro.o validacion.o
	$(CC) $(CFLAGS) pixel.o imagen.o main.o -o $(PROGRAM) $(LDLIBS)

pixel.o: pixel.c pixel.h
	$(CC) $(CFLAGS) -c pixel.c

imagen.o: imagen.c imagen.h pixel.h
	$(CC) $(CFLAGS) -c imagen.c

filtro.o: imagen.c imagen.h filtro.h
	$(CC) $(CFLAGS) -c filtro.c

validacion.o: filtro.h filtro.c validacion.h
	$(CC) $(CFLAGS) -c validacion.c

main.o: pixel.c pixel.h imagen.c imagen.h main.c filtro.c filtro.h validacion.h validacion.c

clean: rm -vf *.o $(PROGRAM)

