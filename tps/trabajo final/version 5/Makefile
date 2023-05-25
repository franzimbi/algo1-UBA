PROGRAM=TP_FINAL_GARCIA_ZIMBIMBAKIS
CC=gcc
CFLAGS=-Wall -Werror -std=c99 -pedantic -g
LDLIBS=-lm


all: $(PROGRAM)

$(PROGRAM): pixel.o imagen.o main.o filtro.o validacion.o procesamiento.o
	$(CC) $(CFLAGS) filtro.o pixel.o imagen.o main.o validacion.o procesamiento.o -o $(PROGRAM) $(LDLIBS)

pixel.o: pixel.c pixel.h
	$(CC) $(CFLAGS) -c pixel.c

imagen.o: imagen.c imagen.h pixel.h
	$(CC) $(CFLAGS) -c imagen.c

filtro.o:  filtro.c filtro.h imagen.h pixel.h
	$(CC) $(CFLAGS) -c filtro.c

validacion.o: validacion.c validacion.h filtro.h
	$(CC) $(CFLAGS) -c validacion.c

procesamiento.o: filtro.h imagen.h procesamiento.c procesamiento.h
	$(CC) $(CFLAGS) -c procesamiento.c

main.o: imagen.h main.c filtro.h pixel.h validacion.h procesamiento.h
	$(CC) $(CFLAGS) -c main.c

clean: rm -vf *.o $(PROGRAM)

