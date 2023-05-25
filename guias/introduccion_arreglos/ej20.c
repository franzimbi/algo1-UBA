#include <stdio.h>
#include <stdlib.h>

typedef unsigned long ulong;


void matriz_identidad(ulong n)
{
ulong dim=n;

	for(int w=0; w<n; w++)
	{
		for(int i=n; i>dim; i--)
		{
			printf("0\t");
		}

		printf("1\t");

		for(int f=1; f<dim; f++)
		{
			printf("0\t");
		}
	printf("\n");
	dim--;
	}
}

int main(void)
{
	ulong dim;

	scanf("%lu", &dim);
	printf("\n\n");
	matriz_identidad(dim);
	printf("\n\n");

	return 0;
}
