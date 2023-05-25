PROGRAM=tp_binetti
CC=gcc
CFLAGS=-Wall -std=c99 -pedantic -g 
LDFLAGS=-lm

all: $(PROGRAM)

$(PROGRAM):  entrada.o imagen.o endiannes.o main.o salida.o procesamiento.o filtro.o pixel.o
	$(CC) $(CFLAGS) entrada.o imagen.o endiannes.o main.o salida.o procesamiento.o filtro.o pixel.o  -o $(PROGRAM) $(LDFLAGS)

imagen.o: imagen.c imagen.h  pixel.h endiannes.h
	$(CC) $(CFLAGS) -c imagen.c

entrada.o: entrada.c entrada.h imagen.h filtro.h
	$(CC) $(CFLAGS) -c entrada.c

pixel.o: pixel.c pixel.h 	
	$(CC) $(CFLAGS) -c pixel.c

endiannes.o: endiannes.c endiannes.h
	$(CC) $(CFLAGS) -c endiannes.c



filtro.o: filtro.c filtro.h pixel.h imagen.h
	$(CC) $(CFLAGS) -c filtro.c



procesamiento.o: procesamiento.c procesamiento.h pixel.h imagen.h
	$(CC) $(CFLAGS) -c procesamiento.c

salida.o: salida.c salida.h filtro.h imagen.h
	$(CC) $(CFLAGS) -c salida.c

main.o: main.c  imagen.h  filtro.h  procesamiento.h   pixel.h  entrada.h
	$(CC) $(CFLAGS) -c main.c


clean:
	rm -vf *.o $(PROGRAM)



