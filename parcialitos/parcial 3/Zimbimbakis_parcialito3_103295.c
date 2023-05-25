#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

/* #define MAX_TPS 10

typedef struct{
    char nombre[MAX_TPS][30]; //arreglo de cadenas donde se guardan los nombres de los trabajos
    int calificacion[MAX_TPS]; // arreglo de las notas de los trabajos, sus valores son enteros y [1,10]
    size_t cantidad; //cantidad de tps
}tps_t;

float tps_nota_final(const tps_t *t)
{
    float total=0;
    for(size_t i=0; i<t->cantidad; i++)
    {
        if(t->calificacion[i] < 4)
            return 2;
        
        total += t->calificacion[i];
    }
    return total/t->cantidad;
}

bool tps_establecer_calificacion(tps_t *t, const char *trabajo, int nota)
{

    if(t->cantidad==MAX_TPS)
        return false;
    
    for(size_t i=0; i<t->cantidad; i++)
    {
        if(!strcmp(trabajo, t->nombre[i]))
        {
            t->calificacion[i] = nota;
            return true;
        }
    }
    

    strcpy(t->nombre[t->cantidad], trabajo);
    t->calificacion[t->cantidad] = nota;
    t->cantidad++;
    return true;
}

int main(void)
{
    tps_t santisi = {{"tp1", "parcial 1", "ejercicio 1", "tp2", "parcial 2"}, {4,5,9,5,8}, 5};

    printf("nota final: %.2f\n", tps_nota_final(&santisi));
    printf("agregando nota: %s\n",tps_establecer_calificacion(&santisi, "tp3", 10) ? "SALIO BIEN" : "SALIO MAL");
    printf("agregando nota: %s\n",tps_establecer_calificacion(&santisi, "tp2", 2) ? "SALIO BIEN" : "SALIO MAL");
    printf("nota final: %.2f\n", tps_nota_final(&santisi));

    for(size_t i=0; i<santisi.cantidad; i++)
    {
        printf("%s\t%i\n", santisi.nombre[i], santisi.calificacion[i]);
    }

    return 0;

} */

bool escribir_cadena(FILE *f, const char *s)
{
    int tamano = strlen(s);
    
    if(fwrite(&tamano,sizeof(int), 1, f)!=1)
        return false;
    
    if(fwrite(s, sizeof(char), tamano, f))
        return false;

    return true;
}

bool escribir_cadenas(const char *ruta, const char *ss[], size_t n)
{
    size_t j=0;
    FILE* fo= fopen(ruta, "wb");
    if(fo==NULL)
        return false;

    for(size_t i=0; i<n;i++)
    {
        int tamano = strlen(ss[i]);
    
        for(j=0; j< tamano; j++)
        {
            if(fwrite(&tamano, sizeof(int), 1, fo))
                return false;
            if(fwrite(&ss[i], sizeof(char),tamano, fo)!= tamano )
                return false;
        }
    } 
    fclose(fo);

    return true;
} 

int main(void)
{
    FILE * fo = fopen("ejercicio2.bin", "wb");

    escribir_cadena(fo, "algoritmo");

    // no llegue a probar escribir_cadenas :(

    fclose(fo);

    return 0;
}



/*#define MAX_STR 4

int main(int argc, char* argv[])
{
    char aux[MAX_STR+1];

    if(argc!=3)
        return EXIT_FAILURE;

    FILE* fo = fopen(argv[2], "rb");
    if(fo == NULL)
        return EXIT_FAILURE;

    for(size_t i=0; i<atoi(argv[1]); i++)
    {
        if(fread(&aux, sizeof(char), MAX_STR, fo)==EOF)
            break;
        fprintf(stdout, "%s\n", aux);
    }

    fclose(fo);

    return 0;
} */