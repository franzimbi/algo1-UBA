#ifndef FILTRO_H
#define FILTRO_H

#include "imagen.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

typedef struct color_tabla colores_tabla;
typedef struct filtro_tabla filtros_tabla;

typedef enum {BLACK, WHITE, RED, LIME, BLUE, YELLOW, 
                   CYAN, MAGENTA, SILVER, GRAY, MAROON, OLIVE, 
                   GREEN, PURPLE, TEAL, NAVY}color_t;

typedef enum {INVERTIR=0, SATURAR=1, GAMA=2, BRILLO=3, CONTRASTE=4, MEZCLAR=5, SEPIA=6, MONOCROMO=7, TOASTER=8, VALENCIA=9}filtro_t;

bool cadena_a_filtro(const char *nombre, filtro_t *filtro);
int numero_de_parametros(filtro_t filtro);
void aplicar_filtro(imagen_t* imagen, filtro_t filtro, int parametro);
void pixel_a_hsv(pixel_t p, short *h, float *s, float *v);
pixel_t pixel_desde_hsv(short h, float s, float v);
pixel_t filtro_invertir(pixel_t p, int _);
pixel_t filtro_saturar(pixel_t p, int porcentaje);
pixel_t filtro_cambiar_gama(pixel_t p, int desplazamiento);
pixel_t filtro_cambiar_brillo(pixel_t p, int porcentaje);
pixel_t filtro_cambiar_contraste(pixel_t p, int porcentaje);
pixel_t filtro_mezclar(pixel_t p, int color);
pixel_t filtro_sepia(pixel_t p, int _);
pixel_t filtro_monocromo(pixel_t p, int porcentaje_umbral);
pixel_t filtro_toaster(pixel_t p, int _);
pixel_t filtro_valencia(pixel_t p, int _);
pixel_t pixel_desde_nombre(const char *nombre);

#endif
