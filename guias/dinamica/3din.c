/*
Implementá una función que reciba una cadena de caracteres y un carácter. La función retorna una copia de la cadena, pero elimina todo lo que esté después del carácter recibido. Utilizá memoria dinámica
*/

#include <stdio.h>
#include <stdlib.h>

char * strip_coment(char s[],char caracter)
{   

    size_t i, j;
    for(j=0;s[j];j++);

    char *copia = malloc(j);
        if(copia==NULL)
            return NULL;

    for(i=0; s[i]; i++)
    {
        if(s[i]==caracter)
            break;

        copia[i] = s[i];
    }
    copia[i]='\0';

    return copia;
}

int main(void)
{
    char * copia =NULL;
    char s[100]= "hola como estas, todo bien?";

    copia = strip_coment(s, ',');
        if(copia==NULL)
            return EXIT_FAILURE;

    printf("%s\n%s\n", s, copia);

    free(copia);

    return EXIT_SUCCESS;
}
