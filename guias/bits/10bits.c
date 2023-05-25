/*

Un sintetizador de una radio digital posee un generador de frecuencia controlado por el siguiente registro:

| bit 7 |   6   |   5   |   4   |   3   |   2   |   1   | bit 0 |
+-------+-------+-------+-------+-------+-------+-------+-------+
|  AFT  |  BAND |   E   |   D   |   C   |   B   |   A   |  SYN  |
+-------+-------+-------+-------+-------+-------+-------+-------+

a.    Escriba el código de una función denominada get_synthesizer_divider() que devuelva por su nombre el factor de división a partir de los bits A, B, C, D y E contenidos en el byte de control.
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define DIVIDER_MASK 0x3E //0011 1110
#define SHIFT_DIVIDER 1
#define BAND_MASK 0x40 //0100 0000
#define SHIFT_BAND 6

int get_synthesizer_divider(uint8_t registro)
{
    return ((registro & DIVIDER_MASK) >> SHIFT_DIVIDER )+1;
}

void set_synthesizer_divider(uint8_t *registro)
{
    *registro &= ~DIVIDER_MASK; //pone EDCBA en 0
}

bool es_am(uint8_t registro)
{
    return(registro & BAND_MASK) >> SHIFT_BAND;
}
int main(void)
{
    uint8_t registro = 0x76;//0111 0110

    printf("el divisor es: %i\n", get_synthesizer_divider(registro));
    printf("%s\n", es_am(registro) ? "es am" : "es pm");

    return EXIT_SUCCESS;
}
