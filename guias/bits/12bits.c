/*

Para un programa que hará uso del puerto paralelo de una PC se necesita disponer de funciones que permitan colocar a nivel lógico 1 ó 0 un bit determinado dentro de un byte a ser presentado al puerto paralelo. Se pide:

Escribir una función llamada :ansi:set(), que obedezca al siguiente prototipo:

uint8_t set(uint8_t datos, short linea);
que reciba un byte sobre la variable datos y el número de línea que será forzada a nivel lógico 1, devolviendo por el nombre el resultado de la operación.

Ejemplo: si en datos se recibe 1000 0001 y linea = 3, se debe retornar el byte 1000 1001.

Dar un ejemplo de invocación de la función.
Idem a) pero para una función llamada :ansi:clear() que coloque a nivel lógico 0 la línea indicada, y devuelva por el nombre el resultado de la operación. Ejemplo: Si en datos se recibe 0111 1100 y línea = 3, se debe devolver el byte 0111 0100.
Dar un ejemplo de invocación de la función.

*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint8_t set(uint8_t datos, short linea)
{
    return datos | (1 << (linea-1)); 
}

uint8_t clear(uint8_t datos, short linea)
{
    return datos | (0 << (linea-1)); 
}

int main(void)
{
    uint8_t registro = 0x16; //0001 0110

    printf("0x%X\n", set(registro, 1));
    printf("0x%X\n", clear(registro, 2));

    return EXIT_SUCCESS;
}
