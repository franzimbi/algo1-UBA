#include <stdio.h>
#include <stdlib.h>

double sumar(double z, int k)
{
    if(k==0)
        return z;
    
    return 1 + sumar(z, k - 1);
}

double multiplicar(double z, int k)
{
    if(k==1)
        return z;

    return z + multiplicar(z,k-1);
}

double exponencial(double z, int k)
{
    if(k==0)
        return 1;

    if(k==1)
        return z;
    
    return z * exponencial(z, k-1);
}

int main(void)
{
    printf("%f\n", sumar(4, 2));
    printf("%f\n", multiplicar(4,2));
    printf("%f\n", exponencial(4, 3));



    return 0;
}

