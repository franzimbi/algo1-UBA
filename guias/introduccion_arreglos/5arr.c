#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


#define MAX 10000

/*Escribir un programa que pida al usuario una cantidad n de valores a generar.
Luego genere n valores enteros en el intervalo [0,10) y cuente la cantidad de 0s, de 1s, de 2s, etc.
Al finalizar, imprima las cantidades calculadas en forma absolutas
y relativas. Realice las validaciones necesarias*/

int obtener_int(char x[], size_t tamano)
{
	fgets(x, MAX, stdin);
	return atoi(x);
}
 
int main(void)
{
	int arreglo[MAX];
	char temp[MAX];
	int cant_valores, cantidad_de_numeros=0;

	srand(time(NULL));

	while( (cant_valores = obtener_int(temp, sizeof(temp))) > MAX)
	{
		printf("sos boludo? menor de 10000. ingresa de nuevo\n");

	}

	for(int i=0; i<cant_valores; i++)
	{
		arreglo[i] = rand() % 10;
		printf("%d\n", arreglo[i]);
	}

	for(int i=0; i<10; i++)
	{
		for(int j=0; j<cant_valores; j++)
		{
			if(i == arreglo[j])
			{
				cantidad_de_numeros ++;
			}
		}
		printf("tenes %d de %ds\n", cantidad_de_numeros, i);
		cantidad_de_numeros = 0;
	}

	return 0;
}
