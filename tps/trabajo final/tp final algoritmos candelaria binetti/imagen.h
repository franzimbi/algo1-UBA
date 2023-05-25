#ifndef IMAGEN_H
#define IMAGEN_H
#include"pixel.h"
#include"endiannes.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>

#define MAX_ANCHO   1000
#define MAX_ALTO    1000


typedef struct {
    pixel_t **lienzo;
    size_t ancho, alto;
} imagen_t;



imagen_t *_imagen_crear(size_t ancho, size_t alto);
imagen_t *imagen_recortar(const imagen_t *imagen, size_t x0, size_t y0, size_t ancho, size_t alto);
imagen_t *imagen_leer_PPM_stdin();
void imagen_escribir_PPM_stdout(const imagen_t *imagen);
imagen_t *imagen_leer_bmp(FILE *f);
void imagen_escribir_BMP(const imagen_t *imagen, FILE *f);
imagen_t *imagen_leer_PPM(FILE *f);
void imagen_escribir_PPM(const imagen_t *imagen, FILE *f);
imagen_t *imagen_clonar(const imagen_t *imagen);
void imagen_destruir(imagen_t *imagen);
void espejar_horizontalmente(imagen_t *imagen);
void espejar_verticalmente(imagen_t *imagen);





#endif