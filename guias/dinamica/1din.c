/*
Implementá una función que reciba una cadena y retorne una copia de la misma, utilizando memoria dinámica, por el nombre. Si por algún motivo no se puede, retornar NULL.
Ahora implementá una función equivalente, pero en vez de retornar la copia por el nombre, que lo haga por la interfaz, mientras que por el nombre retorna un estado, bool, indicando el resultado de la operación.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char* copiar_cadena(char c[], size_t n)
{
    int i;

    char * p = malloc(n);
        if(p == NULL)
            return NULL;
    
    for(i=0; c[i]; i++)
        p[i] = c[i];
    
    p[i] = '\0';

    return p;
}

bool copiar_cadena2(char c[], size_t n, char **v)
{
    int i;

    *v = malloc(n);
        if(*v == NULL)
            return false;
    
    for(i=0; c[i]; i++)
        (*v)[i] = c[i];
    
    (*v)[i] = '\0';

    return true;
}

int main(void)
{
    char buf[100] = {"hola como va"};
  //  char *m = NULL;
    char *v = NULL;
   
   // m = copiar_cadena(buf, 100);
    printf("salio %s\n", copiar_cadena2(buf, 100, &v)==0 ? "bien" : "mal");
    //printf("%s\n%s\n", buf, m);
     printf("%s\n%s\n", buf, v);

   // free(m);
    free(v);

    return EXIT_SUCCESS;
}
