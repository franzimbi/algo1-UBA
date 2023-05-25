/*
implementá una función que reciba una cadena de caracteres, un carácter y una longitud. La misma retorna una copia dinámica de la cadena original, centrada en la longitud especificada y rellenando con el carácter pedido.
*/

#include <stdio.h>
#include <stdlib.h>

char * centrar(const char s[], char relleno, size_t longitud)
{
    size_t m,i,j;
    char * copia=malloc(longitud);
    if(copia==NULL)
        return NULL;

    for(m=0; s[m]; m++);

    m = (longitud-m)/2;

    for(i=0, j=0;s[j];i++)
    {
        if(i<m)
            copia[i]= relleno;
        else
        {
            copia[i]= s[j];
            j++;
        }
    }
    for(;m>0; m--, i++)
    {
        copia[i]=relleno;
    }
    copia[i]='\0';

    return copia;

}

int main(void)
{
    char s[100]="fran";

    char *copia=NULL;

    copia =centrar(s, '*', 8);
    if(copia==NULL)
        return EXIT_FAILURE;
    
    printf("%s\n%s\n", s, copia);

    free(copia);

    return EXIT_SUCCESS;
}
