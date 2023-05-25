#ifndef IMAGEN_H
#define IMAGEN_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <ctype.h>

#include "pixel.h"

typedef struct imagen imagen_t;

imagen_t *imagen_leer_ppm(FILE* f);
imagen_t * imagen_leer_BMP(FILE * f);

void imagen_destruir(imagen_t *imagen);
void imagen_escribir_ppm(const imagen_t *imagen, FILE *f);
void imagen_escribir_BMP(const imagen_t *imagen, FILE *f);

imagen_t *imagen_recortar(const imagen_t *imagen, size_t x0, size_t y0, size_t ancho, size_t alto);
imagen_t *imagen_clonar(const imagen_t *imagen);

void espejar_verticalmente(imagen_t * imagen);
void espejar_horizontalmente(imagen_t * imagen);

size_t obtener_alto(imagen_t * imagen);
size_t obtener_ancho(imagen_t * imagen);
size_t obtener_lienzo(imagen_t * imagen, size_t i, size_t j);
void cambiar_lienzo(imagen_t * imagen, size_t i, size_t j, size_t nuevo);



#endif
