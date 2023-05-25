#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef unsigned long ulong;


int ano_bisiesto(ulong x)
{
	ulong y= x%4;
	ulong w= x%100, z;

	if(y==0 && w!=0)
	{
		printf("es bisiesto\n");
		return 0;
	}
	z = x%400;
	if(z!=0)
	{
		printf("es bisiesto\n");
		return 0;
	}

	printf("no es bisiesto");
	return 0;
}

int main(void)
{
	ulong ano;

	scanf("%lu", &ano);

	ano_bisiesto(ano);

	return 0;
}
