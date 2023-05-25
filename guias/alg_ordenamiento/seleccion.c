#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int *a, int i, int j)
{
    size_t aux = a[i];
    a[i]=a[j];
    a[j]= aux;
}

size_t pos_min(int l[], size_t desde, int hasta)
{
    size_t pos_min = desde;
    
    for(size_t i= desde+1; i<hasta; i++)
    {
        if(l[i] < l[pos_min])
            pos_min = i;
    }

    return pos_min;
}

void seleccion(int *v, int n)
{
    for(size_t i=0; i<n-1; i++)
    {
        size_t p = pos_min(v,i, n-1);
        swap(v, p, i);
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

    seleccion(v, 12);

    for(size_t i=0; i<12; i++)
    {
        printf("%i ", v[i]);
    }

    printf("\n");
    return 0;
}
