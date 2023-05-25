/*
Implementá una función que reciba una cadena de caracteres que contenga varios campos, en formato de campos de ancho fijo y un vector con los anchos de cada campo. La función debe retornar un vector de cadenas con cada campo extraído.

.                          _______
                          |       |
("unodostres",{3,3,4}) -->| split |-->{"uno", "dos", "tres"}
                          |_______|
*/

#include <stdio.h>
#include <stdlib.h>

void destruir(char ** s, size_t ncampos);

char ** split(const char * s, const int * anchos, size_t ncampos)
{
    char **matriz;

    matriz=malloc(ncampos);
    if(matriz==NULL)
        return NULL;
    
    for(int i=0; i<ncampos; i++)
    {
        matriz[i]=malloc(anchos[i]);
        if(matriz[i]==NULL)
        {
            destruir(matriz, ncampos);
            return NULL;
        }
    }

    return matriz;
}

void destruir(char ** s, size_t ncampos)
{
    for(int i=0; i<ncampos; i++)
    {
        free(s[i]);
    }
        free(s);
}

int main(void)
{
    char ** matriz_dinamica =NULL;
    char s[] = "unodostres";
    int a[] = {3,3,4};

    matriz_dinamica = split(s, a, 3);
        if(matriz_dinamica==NULL)
            return EXIT_FAILURE;

    for(int i=0; i<3; i++)
    {
        for(int j=0; j<(a[j]+1); j++)
        {
            printf("%s  ", *matriz_dinamica);
        }
    }

    destruir(matriz_dinamica, 3);
    return EXIT_SUCCESS;
}
