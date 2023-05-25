#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int nro_triangular(int n)
{
    if(n==1)
        return 1;

    return n + nro_triangular(n-1);
}

int main(void)
{
    printf("%i\n", nro_triangular(300));
    return 0;
}
