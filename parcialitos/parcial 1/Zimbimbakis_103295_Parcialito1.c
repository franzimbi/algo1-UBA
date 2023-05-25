#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>


#define MAX_CADENA 100
#define N 3

//ejercicio 1a
void eliminar_caracter (char s[], char c)
{
    char aux[MAX_CADENA];
    int i, w=0;

    for(i=0; s[i]; i++)
    {
        if(s[i] == c)
            continue;
        
        aux[w] = s[i];
            w++;
    }
    aux[w]='\0';
   
    for(i=0; aux[i]; i++)
    {       
        s[i] = aux[i];
    }
    s[i] = '\0';
}

//ejercicio 2a
bool es_matriz_identidad(unsigned int dim, float matrix[dim][dim])
{
    for(int i=0; i<dim; i++)
    {
        for(int j=0; j<dim; j++)
        {
            if(i==j && matrix[i][j]!= 1)
                return false;
            
            if(i != j && matrix[i][j] != 0)
                return false;
        }
    }
    return true;
} 

//funcion para el ejercicio 3

int analizador_notas ()
{
    char cadena[MAX_CADENA] = {0};
    int nota;

    fgets(cadena, MAX_CADENA,stdin);
    nota = atoi(cadena);

    if(nota<0 || nota>10)
        {
        puts("nota invalida\n");
        return -1;
        }
    
    if(nota<4)
        puts("parcialito desaprobado\n");
    
    if(nota>=4)
        puts("parcialito aprobado!\n");
    
    return 0;
}

int main(void)
{
//ejercicio 1b
   char cadena[MAX_CADENA] = "algoritmos y programacion";

    eliminar_caracter(cadena, 'o');
    puts(cadena);

//ejercicio 2b
    float matriz[N][N] = {{1,0,0},{0,1,0},{0,0,1}};

    printf("%d\n", es_matriz_identidad(N, matriz)); 

//ejercicio 3
    analizador_notas();

    return 0;
}
