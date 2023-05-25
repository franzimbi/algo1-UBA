#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*

1. Un procesador usa para enviar datos un registro como el siguiente:

|WLO|WHI|---|D3 |D2 |D1 |D0 |---| 
 7    6   5   4   3   2   1   0

El bit WLO habilita el envío del nibble (medio byte) bajo, el bit WHI habilita el envío del nibble alto y los bits D3,D2,D1,D0 son el nibble a transmitir.
Para enviar un byte se debe:
i. Escribir la mitad baja del byte en D3,D2,D1,D0.
ii. Poner WLO en 1 (para hacer que se mande el nibble bajo).
iii. Escribir la mitad alta del byte en D3,D2,D1,D0.
iv. Poner WHI en 1 (para hacer que se mande el nibble alto).
Programar una función
void enviar_dato(uint8_t *registro, uint8_t dato);
que reciba el registro y un dato y envíe el dato según la secuencia descripta.
Nota: Si se tuviera que enviar el dato 0xAB el nibble alto estará representado por 0xA mientras que el bajo por 0xB.

*/


#define WLO_MASK 0x80 // 1000 0000
#define WHI_MASK 0x40 //0100 0000
#define ALTO_SHIFT 4
#define CLEAN_BYTES 0x1E // 0001 1110
#define BAJO_SHIFT 4

void enviar_dato(uint8_t *registro, uint8_t dato) //dato: AAAA BBBB
{
    *registro = (*registro & CLEAN_BYTES) & (dato >> (ALTO_SHIFT - 1));
    *registro = (*registro) | WLO_MASK;

     *registro = (* registro & CLEAN_BYTES) & ( dato << (BAJO_SHIFT - 1));
    *registro = (*registro) | WHI_MASK;

}


/*

a. Implementar la función:
char **extraer_cadenas(const char *ss[], size_t sn, size_t indices[], size_t indicesn);
que reciba un arreglo de cadenas de caracteres ss de longitud sn y que devuelva un arreglo de cadena de caracteres de longitud indicesn que contenga únicamente las cadenas que correspondan a los indices indicados. Todo debe estar contenido en memoria nueva.
Ejemplo, si se llama a la función con ss = {"hola", "que", "tal", "estas"} (sn = 4) y con indices = {1, 3} (indicesn = 2) se debe devolver {"que", "estas"}.
b. Implementar la función:
void liberar_cadenas(char *ss[], size_t sn);
que reciba ss, un arreglo dinámico de cadenas de caracteres dinámicas de longitud sn y libere toda su
memoria asociada.

*/
/*

void liberar_cadenas(char *ss[], size_t sn)
{
    for(size_t i=0; i<sn; i++)
    {
        free(ss[i]);
    }
    free(ss);
}

char **extraer_cadenas(char *ss[], size_t sn, size_t indices[], size_t indicesn)
{
    size_t tamano;
    char **nueva_cadena = malloc(sizeof(char*) * indicesn);
    if(nueva_cadena==NULL)
        return NULL;

    for(size_t i=0; i<indicesn; i++)
    {
        tamano = strlen(ss[indices[i]]);
        nueva_cadena[i] = malloc(sizeof(char) * (tamano +1));
        if(nueva_cadena[i] == NULL)
        {
            liberar_cadenas(ss,i);
        }
        strcpy(nueva_cadena[i], ss[indices[i]]);
    }
    return nueva_cadena;
}
*/

/*

 Se tiene representado a un vector de enteros en una estructura que contiene un vector dinámico y su longitud.
a. Declarar la estructura del vector.
b. Redefinir la estructura declarada como el tipo vector_t.
c. Implementar la función
bool vector_agregar_elemento(vector_t *v, int elemento); que agregue el elemento al final del vector v.
En caso de no poder agregarse el elemento se debe devolver false sin modificar el vector recibido. Caso contrario debe devolverse true.

*/

/*
#define TAM_INICIAL 2

typedef struct{
    int * vec;
    size_t lon;
} vector_t;

bool vector_agregar_elemento(vector_t *v, int elemento)
{
    int *aux;

    aux = realloc(v->vec, (v->lon)+1);
    if(aux==NULL)
    {
       return false;
    } 
    else
    {
        v->vec = aux;
    }

    v->vec[(v->lon)] = elemento;



    v->lon += 1 ;

    return true; 
}
*/

int main(void)
{

// EJERICIO 1

    uint8_t registro = 0xFF;
    uint8_t dato = 0xA2;

    enviar_dato(&registro, dato);

    printf("0x%X\n", registro); 


//EJERCICIO 2

/*char *ss[] = {"hola" , "que", "tal", "estas"};
char **n;
size_t indices[] = {1,3};

n = extraer_cadenas(ss, 4, indices, 2);
if(n==NULL)
    return 1;

for(size_t i; i<2; i++)
{
    printf("%s\n", n[i]);
}

liberar_cadenas(n, 2); */


//ejercicio3

/*
int *vector = malloc(sizeof(int) * 2);
    vector[0] = 1;
    vector[1] = 2;
vector_t enteros ={ vector, 2};


printf("%s \n", vector_agregar_elemento(&enteros, 4) ? "BIEN" : "MAL");

for(size_t i; i< (enteros.lon); i++)
{
    printf("%i\n", enteros.vec[i]);
}
    free(enteros.vec);

*/

    return 0;
}