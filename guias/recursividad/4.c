#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool es_potencia(int n, int b)
{
    if(b==n)
        return true;
    
    if(b<n)
        return false;

    return es_potencia(n, b/n);
}

int main(void)
{
    if(es_potencia(4, 1024)==true)
    {
        printf("es potencia\n");
    }else{
        printf("no es potencia\n");
    }

    return 0;
}
