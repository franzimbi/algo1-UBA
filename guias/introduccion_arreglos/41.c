#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 100

double inverso(long nro)
{
	return 1.0 / nro;
}

double raiz(long nro)
{

long complex;

	if(nro>=0)
	{
	return sqrt(nro);
	}

	complex = nro * (-1);

return sqrt(complex);

}

int main (void)
{

char nro[MAX];
long valor=0;


fgets(nro, MAX - 1, stdin);


valor = atoi(nro);

if(valor>=0)
{
	printf("la raiz es: %f\n", raiz(valor));
}else
{
	printf("la raiz es compleja: %f i\n", raiz(valor));	
}

if(valor!=0)
{
	printf("el inverso es: %f\n", inverso(valor));
}else 
	printf("no tiene inverso\n");

return 0;
}

