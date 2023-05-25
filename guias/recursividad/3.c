#include <stdio.h>
#include <stdlib.h>

void imprimir_espejado(int n)
{
    if(n<10)
    {    
        printf("%i\n", n);
        return;
    }
    printf("%i", n%10);
    imprimir_espejado(n/10);
}

int main(void)
{
    imprimir_espejado(6543);

    return 0;
}
