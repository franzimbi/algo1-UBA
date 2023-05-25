/*

 Un dispositivo de adquisición de datos se comunica mediante protocolo I2C. Para realizar la transmisión de un byte el mismo se envía en dos paquetes distintos, uno con su parte alta y otro con su parte baja. El paquete para la parte alta es 01000xxx donde xxx son los 3 bits más pesados del byte a transmitir, mientras que el paquete de la parte baja es 011xxxxx donde xxxxx son los 5 bits más livianos del byte a transmitir.
Por ejemplo si se quisiera transmitir el byte 10111001 se deberá codificar como los paquetes 01000101 y 01111001.
a. Implementar la función uint8_t obtener_byte(uint8_t alta, uint8_t baja); que reciba la par- te alta y la parte baja de una transmisión y devuelva el byte recibido.
b. Implementar la función void generar_byte(uint8_t byte, uint8_t *alta, uint8_t *baja); que reciba un byte a transmitir y devuelva la parte alta y baja de los paquetes a enviar.

*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*#define ALTOS_MASK 0x7//0000 0111 -> 2^0 + 2^1 +2^2
#define BAJOS_MASK 0x1F //0001 1111
#define PAQUETE_ALTO 0x40
#define PAQUETE_BAJO 0x60
#define ALTOS_SHIFT 5


uint8_t obtener_byte(uint8_t alta, uint8_t baja) //0100 0xxx + 011y yyyy  =  xxxy yyyy
{
    return (alta << ALTOS_SHIFT) | (baja & BAJOS_MASK);
}

void generar_byte(uint8_t byte, uint8_t *alta, uint8_t *baja) 
{
    *alta = PAQUETE_ALTO | (byte >> ALTOS_SHIFT);
    *baja = PAQUETE_BAJO | (byte & BAJOS_MASK);
}

int main (void)
{
    uint8_t registro = 0x2F; //0010 1111
    uint8_t alto;
    uint8_t bajo;
    uint8_t alto2 = 0x45, bajo2 = 0x75;  //0100 0101 0111 0101

    printf("0x%X\n", obtener_byte(alto2,bajo2)); //101 10101  101 10101
    
    generar_byte(registro, &alto, &bajo);
    printf("0x%X\t0x%X\n", alto, bajo); // 0100 0001 0110 1111 

    return 0;
} */

/*
2. Se tiene definida una estructura

typedef struct {
unsigned int id;
char nombre[MAX_NOMBRE]; float precio;
} producto_t;

que representa a un producto.
Escribir una función
char *producto_a_csv(const producto_t *producto);
que dado un producto devuelve una cadena de caracteres que representa al mismo en formato CSV.
Por ejemplo, para el producto {123, "Manzana red delicious", 85.23} puede devolverse la cadena "123,Manzana red delicious,85.23".
(Sugerencia: Usar la función de biblioteca sprintf().)
*/
/*
#define MAX_NOMBRE 20

typedef struct {
unsigned int id;
char nombre[MAX_NOMBRE];
float precio;
} producto_t;

char *producto_a_csv(const producto_t *producto)
{
    char *cadena_csv = malloc(sizeof(char) * 50);
    if(cadena_csv==NULL)
        return NULL;

    sprintf(cadena_csv, "%i, %s, %.2f", producto->id, producto->nombre, producto->precio);

    return cadena_csv;
}

int main(void)
{
    producto_t arroz = {1234, "arroz gallo oro", 90.3};

    char *p = producto_a_csv(&arroz);
    printf("%s\n", p);
    free(p);

    return 0;
}
*/

/*

3. Implementar una función
int *generar_ruido(int modulo, size_t *n);
que internamente genere números con rand() % modulo.
Teniendo un vector donde guardar los números el algoritmo será así:
1. Se genera un número n.
 2. Si n != 0:
a. Se generan n números que se agregan al vector de números generados.
b. Se vuelve al paso 1.
Se deberá devolver el vector por el nombre de la función así como su longitud a través del parámetro n.

*/

int *generar_ruido(int modulo, size_t *tamano)
{
    size_t i=0;
    int *numeros_generados=NULL;
    int *aux=NULL; 
    srand(time(NULL));
    
    int n = rand() % modulo;
    if(n==0)
        return NULL;

    while(n!=1)
    {
        aux = realloc(numeros_generados, sizeof(numeros_generados) + sizeof(int) * n);
        if(aux==NULL)
        {
            free(numeros_generados);
            return NULL;
        }else
        {
            numeros_generados = aux;
        }

        for(size_t j=0; j<=n; j++)
        {
            numeros_generados[j+i] = rand() % modulo; 
        }
        i += n;
        n = rand() % modulo;
    }

    *tamano = i;
    return numeros_generados;
}

int main(void)
{
    int modulo = 14;
    size_t tamano;
    int *p = generar_ruido(modulo, &tamano);

    for(size_t i=0; i<tamano; i++)
    {
        printf("%i   ", p[i]);
    }

    printf("\n");
    free(p);

    return 0;
}

