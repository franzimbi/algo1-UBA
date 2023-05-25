#include <stdio.h>

int main(void)
{
int i = 3, * pint;
float f = 10.0;

pint = &i;
printf("%p\n", &pint);
*pint = 10;
printf("%d\n", *pint);
*pint = f;
printf("%p\n", *pint);
pint = &f;
printf("%p\n", pint);
pint = 4321;
printf("%p\n", pint);

return 0;
}