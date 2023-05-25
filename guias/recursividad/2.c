#include <stdio.h>
#include <stdlib.h>

int digititos(int n)
{
    if(n < 10)
        return 1;

    return 1 + digititos(n/10); 
}

int main(void)
{
    printf("%i\n", digititos(244453));

    return 0;
}
