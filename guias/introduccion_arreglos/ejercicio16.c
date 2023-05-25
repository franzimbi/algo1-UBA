#include <stdio.h>

void espejado(unsigned long x)
{
	long y, w;

	for(y=10; y<x; x/=10)
	{
		w = x%y;
		if(w<10)
		{
			printf("%ld", w);		
		}else{
	printf("%d", 0);}
	
	}
	printf("%ld", x);
	printf("\n");	
}

int main(void)
{
	long numero;

	scanf("%lu", &numero);
	espejado(numero);

	return 0;
}
