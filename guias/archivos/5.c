#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

//recibe dos punteros a palabras, si son iguales devuelve 0, si son distintas devuelve algo distinto de 0.
bool wordcmp(char* w1, char* w2)
{
    size_t i;
    for(i=0; *(w1+i) != *(w2+i) ; i++)
    {
        if(isspace(*(w1+i)) !=0)
            return true;
        if(*(w1+i)==EOF)
            return true;
    }

    return false;
}

int main(int argv, char* argc[])
{
    char buf[100];
    char* palabra;
    bool palabra_similar;

    for(size_t i=2; i<=argv; i++)
    {
        FILE* archivo = fopen(argc[i], "rt");
        if(archivo==NULL) 
            return EXIT_FAILURE;

    fprintf(stderr, "abri archivo %s\n", argc[i]);

        fgets(buf, 100, archivo);
        for(size_t j=0; buf[j]!='\0' && buf[j]!= '\n'; j++)
        {

            fprintf(stderr, "fila del archivo %s nro %zu \n", argc[i], i);

            if(buf[j]==argc[1][0])
            {

                fprintf(stderr, "buf[j]: %zu \n", j);

                palabra_similar = wordcmp(&buf[j], &argc[1][0]);
                if(palabra_similar==true)
                {
                    fprintf(stdout, "%s\n", buf);
                }
            }
            fgets(buf, 100, archivo);
        }
        fclose(archivo);
    }

    return EXIT_SUCCESS;
}