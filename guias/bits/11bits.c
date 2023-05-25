/*

Para un subsistema de comunicaciones basado en un microcontrolador, que forma parte de un equipo de medición, se debe programar el registro de control de periféricos (SPCR), el cual tiene la siguiente estructura:

| bit 7 |   6   |   5   |   4   |   3   |   2   |   1   | bit 0 |
+-------+-------+-------+-------+-------+-------+-------+-------+
|  SPIE |  SPE  |   -   |   -   |  CPOL |  SPR1 |  SPR0 |   -   | SPCR
+-------+-------+-------+-------+-------+-------+-------+-------+

*/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#define SPIE_MASK 0x80 //1000 0000
#define SPIE_SHIFT 7
#define CPOL_MASK 0x08 //0000 1000
#define CPOL_SHIFT 3
#define DIVFACT_MASK 0x06 //0000 0110
#define DIVFACT_SHIFT 1


struct frecuencias_reloj
{
    uint8_t binary;
    int factor;
    char frecuencia[10];
};

const struct frecuencias_reloj frecuencias[]
{
    {0x0, 2, "1MHz"},
    {0x01, 4, "500kHz"},
    {0x02, 16, "125kHz"},
    {0x03, 32, "62,5kHz"}
};

bool getSPIE(uint8_t r)
{
    return (r & SPIE_MASK) >> SPIE_SHIFT;
}

bool getCPOL(uint8_t r)
{
    return (r & CPOL_MASK) >> CPOL_SHIFT;
}

void getCOMControl(uint8_t r)
{
    uint8_t divisor = (r & DIVFACT_MASK) >> DIVFACT_SHIFT;
    int i;

    for(i=0; frecuencias[i].binary == divisor; i++);
    printf("el factor de division es: %d, con una frecuencia de reloj de: %s", 
    frecuencias[i].factor, frecuencias[i].frecuencia);
}

void getPrescalingFactor(uint8_t r, int *SPIE, int *CPOL,
                         int *factor_div, char s[])
{
    *SPIE = (r & SPIE_MASK) >> SPIE_SHIFT;
    *CPOL = (r & CPOL_MASK) >> CPOL_SHIFT;
    *factor_div = (r & DIVFACT_MASK) >> DIVFACT_SHIFT;

}

void setCPOL(uint8_t *control, bool on)
{
    *control &= ~CPOL_MASK;
    *control |= (on << CPOL_SHIFT);
}

int main(void)
{
    uint8_t registro = 0x08; //0000 1000

    setCPOL(&registro, 1);
    printf("0x%X\n", registro);
    return EXIT_SUCCESS;
}
