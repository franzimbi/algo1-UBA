#include <stdio.h>

int main(void)
{
	int a, b;

	for(a=0; a<=6; a++)
	{
		for(b=a; b<=6; b++)
		{
			printf("%d-%d\t", a, b);
			}
	printf("\n");
	}
return 0;
}
