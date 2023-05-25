#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insertar_ordenado(int l[], int i)
{
    int aux = l[i];
    size_t j;

    for( j=i-1; j>=0 && l[j]>aux; j--)
    {
        l[j+1] = l[j];
    }

    l[j+1] = aux;
}


void insercion(int l[], int n)
{
    for(size_t i=0; i<n; i++)
    {
        insertar_ordenado(l, i);
    }
}

int main(void)
{
    int v[] = {6,5,2,9,1,8,12,6,0,8,19,22};

    for(size_t i=0; i<12; i++)
    {
        printf("%i ", v[i]);
    }
    printf("\n");

    insercion(v, 12);

    for(size_t i=0; i<12; i++)
    {
        printf("%i ", v[i]);
    }

    printf("\n");
    return 0;
}
