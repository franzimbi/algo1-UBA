#include <stdio.h>
#include <math.h>

#define PI 3.141592653589793

#define ANCHO 640
#define ALTO 480
#define MAXIMO 255

#define X0 (ANCHO / 2)
#define Y0 (ALTO / 2)

#define FRECUENCIA 0.02


double distancia(float x0, float y0, float x1, float y1)
{
	return sqrt((x0 - x1)*(x0 - x1) + (y0 - y1)*(y0 - y1));
}

int seno_escalado(double t, float f, int max)
{
	return (max / 2.0) * ( sin(2*PI*f*t) + 1);
}

int main(void)
{

int x, y;
	printf("P2\n");
	printf("%d\t%d\n", ANCHO, ALTO);
	printf("%d\n", MAXIMO);

	for(y=0; y<ALTO; y++)
	{
		for(x=0; x<ANCHO; x++)
		{
			printf("%d\t", seno_escalado(distancia(X0, Y0, x, y), FRECUENCIA, MAXIMO));
		}
	putchar('\n');
	}
return 0;

}
