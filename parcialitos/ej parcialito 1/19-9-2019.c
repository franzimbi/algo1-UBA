#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


#define MAX 50
#define MAX_AUX 50
#define N 3
#define M 2

void left_trim(char cadena[])
{
	char aux[MAX_AUX]; 
	int i=0, w=0;

	while(cadena[i]==' ')
	    i++

	for(w=0; cadena[i]; w++)
	{
		aux[w] = cadena[i];
		i++;
	}
    aux[w] = '\0';
	i=0;
    
    for(int j=0; aux[j]; j++)
	{
		cadena[i] = aux[j];
		i++;
	}
	cadena[i] = '\0';
}

float sumar_positivo(int filas, int columnas, float matriz[][columnas])
{
    float resultado=0;

    for(int i=0; i<filas; i++)
    {
        for(int j=0; j<columnas; j++)
            if(matriz[i][j]>0)
                resultado+=matriz[i][j];
    }
    return resultado;
}

unsigned long  contador_de_blancos()
{
	long cant_blancos=0;
	int c;

	while((c=getchar()) != EOF)
	{
		if((isspace(c)) != 0)
			cant_blancos ++;
	}

	return cant_blancos;
}

int main(void)
{
	char cadena[MAX]={"    hola putoo"};
    float matriz[][M]={1,2,-1,-2,-1,8.4};

	left_trim(cadena);
    puts(cadena);

printf("la suma de los positivos es: %.2f\n", sumar_positivo(N,M,matriz));

printf("la cantidad de caracteres blancos es: %lu\n", contador_de_blancos());

	return 0;
}


