#include <stdio.h>

void suma(int a, int b, int * suma)
{
    *suma = a+b;
}

int main(void)
{
int a=1, b=2, resultado;

    suma(a,b,&resultado);
    printf("%d\n", resultado);

    return 0;
}