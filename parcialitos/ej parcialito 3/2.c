#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*#define INFINITY 99999999999999999;

typedef struct{
    float vector[20]; // el valor de las coordenadas del vector existente en los reales^dim
    unsigned int dim; // la dimension del vector
} vector_t;

size_t vector_dimension(const vector_t *v)
{
    return v->dim;
}

float vector_producto_interno(const vector_t *a, const vector_t *b)
{
    float total=0;

    if(a->dim != b->dim)
        return INFINITY;

    for(size_t i=0; i<(a->dim); i++)
    {
        total += a->vector[i] * b->vector[i];
    }

    return total;
}

int main(void)
{
    vector_t vec1 = {{1,2,3,4}, 4};
    vector_t vec2 = {{2,1,2}, 3};

    printf("dimension de vec1: %zu\n", vector_dimension(&vec1));
    printf("producto interno vec1 con vec2: %.2f\n", vector_producto_interno(&vec1, &vec2));

    return 0;
}
*/


char *leer_cadena(FILE *f)
{
    int n;

    fread(&n, sizeof(int), 1, f);
    
    char* string = malloc(sizeof(char) * (n+1));
    if(string==NULL) return NULL;
    
    if(n==EOF)
    {
        string[0]='\0';
        return string;
    }

    for(size_t i=0; i<n; i++)
    {
        char c;
        fread(&c, sizeof(char), 1,f);
        string[i] = c;
    }
    string[n++] = '\0';
    return string;
}

/*int main(void)
{
    FILE * f = fopen("ejercicio2.bin", "wb");
    int nro=4;
    char palabra[7] = {'h','o','l','o'};

    fwrite(&nro, sizeof(int), 1, f);
    fwrite(&palabra, sizeof(char), 4,f);

    nro=2;
   char palabra1[2]= {'f', 'z'};

    fwrite(&nro, sizeof(int), 1, f);
    fwrite(&palabra1, sizeof(char), 2,f);

    nro=7;
    char palabra2[7]= {'b', 'o', 'q', 'u', 'i', 't','a'};

    fwrite(&nro, sizeof(int), 1, f);
    fwrite(&palabra2, sizeof(char), 7,f);

    fclose(f);

    f = fopen("ejercicio2.bin", "rb");

    char * devolucion = leer_cadena(f);

    printf( "%s\n", devolucion);

    fclose(f);
    free(devolucion);

    return 0;
} 
*/
int main(int argc, char* argv[])
{
    FILE* f = fopen(argv[1], "rb");

    for(size_t i=0; i<atoi(argv[2]); i++)
    {
        char* cadena = leer_cadena(f);
        if(cadena==NULL)
            return EXIT_FAILURE;

        fprintf(stdout, "%s\n", cadena);
        free(cadena);
    }

    return 0;
} 