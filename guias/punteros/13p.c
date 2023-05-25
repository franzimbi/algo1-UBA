/*
(búsqueda binaria) Implemente una función similar de búsqueda, utilizando búsqueda binaria. Prototipos:
*/

#include <stdio.h>

#define MAX_VECTOR 100

int * busqueda_binaria(int * v, /* vector donde buscar */
                             size_t n,      /* largo del vector */
                             int objetivo,  /* elemento a buscar */
                             size_t izq)    /* franja del vector donde buscar, */
                                            /* delimitada por izq y der */

{
    int i = izq/2;
    int * p=NULL;

    if(n<izq)
        return NULL;

    while( v[i]!=objetivo || i< izq)
    {   
        if(v[i]==objetivo)
            return p = v[i];
        if(v[i] < objetivo )
        {  i /= 2;
        }else 
        {
            i = i + i/2;
        }
    }
    return NULL;
}

int main(void)
{
    int v[MAX_VECTOR] = {0};
    int objetivo= 32;

    for(int i=1; i<MAX_VECTOR; i++)
    {
        v[i] = i;
    }

    printf("v empieza en: %d\n", &v[0]);

    printf("el %d esta en: %d\n", objetivo, busqueda_binaria(&v, MAX_VECTOR, objetivo, MAX_VECTOR));

    return 0;
}
