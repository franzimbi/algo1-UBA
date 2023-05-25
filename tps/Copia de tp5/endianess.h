#ifndef ENDIANESS_H
#define ENDIANESS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void escribir_int16_little_endian(FILE *f, int16_t v);
void escribir_int32_little_endian(FILE *f, int32_t v);
size_t int32_a_big_endian(int32_t nro);

#endif
