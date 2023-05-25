#include "endianess.h"
//#include "endianess.h"

// recibe un archivo abierto y un nro de 16 bits y lo escribe en little-endian
void escribir_int16_little_endian(FILE *f, int16_t v)
{
    uint8_t vec[2];
    vec[1]= v >> 8;
    vec[0] = (v & 0x00FF);

    fwrite(vec, sizeof(uint8_t), 2, f);
}

void escribir_int32_little_endian(FILE *f, int32_t v)
{
    uint8_t vec[4];
    vec[0] = v & 0x000000FF;
    vec[1] = (v & 0x0000FF00) >> 8;
    vec[2] = (v & 0x00FF0000) >> 16;
    vec[3] = (v & 0xFF000000) >> 24;

    fwrite(vec, sizeof(uint8_t), 4, f);
}

size_t int32_a_big_endian(int32_t nro)
{
    uint8_t vec[4];
    vec[0] = nro & 0x000000FF;
    vec[1] = (nro & 0x0000FF00) >> 8;
    vec[2] = (nro & 0x00FF0000) >> 16;
    vec[3] = (nro & 0xFF000000) >> 24;

    return vec[0] | vec[1] | vec[2] | vec[3];
}

