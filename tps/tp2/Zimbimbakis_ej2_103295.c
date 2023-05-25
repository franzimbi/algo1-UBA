#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_ALTO 1000
#define MAX_ANCHO 1000
#define MAX_AUX 10

typedef unsigned char pixel_t;

int leer_entero()
{
	char buffer[MAX_AUX] = {0}, c;
	size_t i=0;
	
	c = getchar();

	while(c=='#' || isspace(c) || c==EOF)
	{
	if(c=='#')
		while( (c=getchar())!='\n' && c!=EOF);

	if(c==EOF)
		return -1;
	
	c=getchar();
	}

	while( !isspace(c) && c != EOF)
	{
		buffer[i] = c;
		i++;
		c=getchar();
	}

	if(c==EOF)
		return -1;

	buffer[i]='\0';
	return atoi(buffer);
}

void imprimir_pgm(pixel_t imagen[MAX_ALTO] [MAX_ANCHO], size_t ancho, size_t alto)
{
	printf("P2\n");
	printf("%zu\t%zu\n", ancho, alto);
	printf("255\n");
	for(int i=0; i<alto; i++)
	{
			for(int j=0; j<ancho; j++)
				printf("%hhu\n", (pixel_t) imagen[i][j]);
	putchar('\n');
	}
	/* %hhu es lo q me dice mi compilador que ponga para que compile, quizas sea pq estoy en macOS */ 

}

void invertir_valores(pixel_t imagen[MAX_ALTO][MAX_ANCHO], size_t ancho, size_t alto)
{

	for(int i=0; i<alto; i++)
	{
		for(int j=0; j<ancho; j++)
		{
			imagen[i][j] = 255 - imagen[i][j];
		}
	}
}

void espejar_horizontalmente(pixel_t imagen[MAX_ALTO][MAX_ANCHO] , size_t ancho, size_t alto)
{
	size_t temp;

	for(size_t i=0; i<alto; i++)
	{
		for(size_t j=0; j<=ancho/2 ; j++)
		{
			temp = imagen[i][j];
			imagen[i][j] = imagen[i][ancho-j-1];
			imagen[i][ancho-j-1] = temp;
		}	
	}
}

int main (void)
{
	pixel_t imagen[MAX_ALTO][MAX_ANCHO];
	int alto, ancho, pixel=0;

	leer_entero(); //P2
	ancho = leer_entero(); //ancho
	alto = leer_entero(); //alto
	leer_entero(); //cantidad de pixeles

	for(int i=0; i<alto; i++)
	{
		if(pixel == -1)
			break;

		for(int j=0; j<ancho; j++)
		{
			pixel = leer_entero();
			if(pixel == -1)
				break;

			imagen[i][j] = pixel;
		}
	}

	espejar_horizontalmente(imagen, ancho, alto);
	invertir_valores(imagen, ancho, alto);
	
	imprimir_pgm(imagen, ancho, alto);
return 0;
}
