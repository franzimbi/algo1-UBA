#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char * readline(FILE * archivo)
{
    char * str = malloc(sizeof(char) * 100);
        if(str==NULL) return NULL;

    fgets(str, 100, archivo);

    return str;
}

bool readline2(FILE * archivo, char ** cadena_leida)
{
    *cadena_leida = malloc(sizeof(char) * 100);
        if(cadena_leida==NULL)
            return false;

    fgets(*cadena_leida, 100, archivo);
    return true;
}

int main(void)
{
    return 0;
}
