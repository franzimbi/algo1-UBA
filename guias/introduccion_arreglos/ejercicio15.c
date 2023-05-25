#include <stdio.h>

unsigned long factorial(unsigned long x)
{
	unsigned long total = 1, y;

	for(y=1;y<=x; y++)
	{
		total = total * y;
	}
	return total;
}

int main(void)
{
unsigned long n;

	scanf("%ld", &n);

	printf("%lu\n", factorial(n));

	return 0;
}
