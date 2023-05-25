#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int mayor_nro_vector(int *v, int n)
{
    if(n==2)
        return v[0] > v[1] ? v[0] : v[1];
    
    int x = mayor_nro_vector(v, n-1);
    return x > v[n] ? x : v[n];
}

int main(void)
{
    int v[]={1,6,3,4,10,2,32,45,20,1,0,2,3,4,12};
    printf("%i\n", mayor_nro_vector(v, 15));
    return 0;
}
