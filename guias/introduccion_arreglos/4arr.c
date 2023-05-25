#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define max 8

//Escribir un programa que permita ingresar 
//una cantidad fija de números, los almacene en un 
//arreglo y luego imprima la media y la varianza del mismo.

float medie(int arregle[], size_t tamano)
{
	float temp=0;

	for(int i=0; i<tamano; i++)
	{
		temp += arregle[i];	
	}

	return temp/(tamano);
}


int main(void)
{
	char ashegle[max];
	int arregle[max];

	for(int i=0; i<max; i++)
	{
		fgets(ashegle, max, stdin);
		arregle [i] = atoi(ashegle);
	}

	printf("la medie es: %f\n", medie(arregle, sizeof(arregle)/4));

return 0;
}
