/*
(búsqueda lineal) Implementar una función que reciba un vector, su longitud, un número objetivo a buscar y retorne un puntero a la posición en la que se encuentra. ¿Qué ocurre en caso que el objetivo no se encuentre y qué se retorna? Implemente 2 versiones de la función, utilizando los siguientes prototipos:
*/

#include <stdio.h>
#include <stdbool.h>

void * busqueda_lineal(int * v, size_t n, int objetivo)
{
    int i;

    for(i=0; i<n ; i++)
    {
        if(*(v+i) == objetivo)
            return (v+i);
    }
    return NULL;
}

bool busqueda_lineal2(int * v, size_t n, int objetivo, int ** resultado)
{
    int i;

    for(i=0; i<n ; i++)
    {
        if(*(v+i) == objetivo)
        {
            *resultado = (v+i);
            return true;
        }
    }
    return false;
   
}

int main(void)
{
    int v[10] = {1,2,3,4,5,6,7,8,9,0};
    
    int objetivo = 2;
    int resultado;
    int *p = &resultado;

    printf("v empieza en: %d\n", v);
    /*printf("%d esta en: %d\n", objetivo, busqueda_lineal(v, (sizeof(v))/4, objetivo)); */

    printf("%ssalio bien\n", busqueda_lineal2(v, (sizeof(v))/4, objetivo, &p) ? "si " : "no ");

    printf("%d esta en: %d\n", objetivo, p);

    return 0;
}
