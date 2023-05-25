#include <stdio.h>
#include <stdlib.h>

int busqueda_binaria(const int v[], int n, int elemento)
{
    int izq=0, der= n-1, medio;

    while(izq<=der)
    {
        medio =  (der +izq)/2;

        if(v[medio]==elemento)
            return medio;
        
        if(v[medio] > elemento)
        {
            der = medio -1;
        }else
        {
            izq = medio+1;
        }
    }

    return -1;
}

int main(void)
{
    const int v[]= {1,2,3,4,5,6,7,10,12,14,17,20,24,27,35,40,50,60,63,69,70,72,73,74,75,80,81,83,84,85,88,89,90,95,97,100};

    int e=34;

    printf("el nro %i esta %i\n", e, busqueda_binaria(v, sizeof(v)/sizeof(int), e));

    return 0;
}

