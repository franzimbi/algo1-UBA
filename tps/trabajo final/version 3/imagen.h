#ifndef IMAGEN_H
#define IMAGEN_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <ctype.h>
#include "pixel.h"

//typedef struct imagen imagen_t;

imagen_t *imagen_leer_ppm(FILE* f);
void imagen_destruir(imagen_t *imagen);
void imagen_escribir_ppm(const imagen_t *imagen, FILE *f);
imagen_t *imagen_recortar(const imagen_t *imagen, size_t x0, size_t y0, size_t ancho, size_t alto);
imagen_t *imagen_clonar(const imagen_t *imagen);
void imagen_escribir_BMP(const imagen_t *imagen, FILE *f);
imagen_t * imagen_leer_BMP(FILE * f);
void espejar_verticalmente(imagen_t * imagen);
void espejar_horizontalmente(imagen_t * imagen);


#endif
