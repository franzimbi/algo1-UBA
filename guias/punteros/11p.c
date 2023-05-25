/*
Implementar una función que reciba 2 vectores y sus longitudes, y retorne un valor booleano, por la interfaz, si los vectores son iguales.
*/

#include <stdio.h>
#include <stdbool.h>

#define MAX 10

bool son_iguales(const char *a, const char *b, size_t size_a, size_t size_b)
{
    if(size_a != size_b)
    return false;

    for(char i=0; i<size_a; i++)
    {    if(*(a+i) != *(b+i))
            return false;
    }

    return true;
}

int main (void)
{
    float a1[MAX] = {1,2,3,4,5,6,7,8,9,0};
    float a2[MAX] = {1,2,30,4,50,6,7,80,9,0};

    printf("a1 y a2 %s son iguales\n", son_iguales((char *) a1,(char *) a2, sizeof(a1), sizeof(a2)) ? "si" : "no");

    return 0;
}
