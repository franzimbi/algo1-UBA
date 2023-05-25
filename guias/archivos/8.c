#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE* f= fopen("ejercicio7.bin", "rb");

    int* vector = malloc(sizeof(int) * 500);
    int* vector_aux;
    int espacio=500 , usado=0;
    if(vector==NULL) return EXIT_FAILURE;
    int aux;
    size_t i;

    fread(&aux, sizeof(int), 1, f);

    for(i=0; aux != EOF; i++)
    {
        vector[i]=aux;
        usado++;
        if(espacio<=usado)
        {
            vector_aux = realloc(vector, sizeof(int) * (espacio+100));
                if(vector_aux==NULL) break;
                else{
                        //free(vector);
                        vector=vector_aux;
                }
            espacio= espacio +100;
        }
        fread(&aux, sizeof(int), 1, f);
    }

    for(size_t j=0; j<i; j++)
    {
        fprintf(stdout, "%d\n", vector[j]);
    }

    fclose(f);
    free(vector);

    return EXIT_SUCCESS;
}
