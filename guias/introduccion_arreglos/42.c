#include <stdio.h>
#include <stdlib.h>

#define MAX 4

typedef unsigned long ulong;


int dia_semana (long dia)
{

char dias[][10] = {"domingo","lunes", "martes", "miercoles", "jueves", "viernes", "sabado"};

	
printf("hoy es: %s\n", dias[dia%7]);
return 0;
}

int main(void)
{
	char nro[MAX];
	long x; 

	fgets(nro, MAX, stdin);
	x = atoi(nro);

while(x>366 || x<=0)
	{
		printf("nro incorrecto, reintenta\n");
		fflush(stdin);
		fgets(nro, MAX, stdin);
		x = atoi(nro);
		
	} 

	dia_semana(x);

	return 0;

}
