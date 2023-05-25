#ifndef FILTRO_H
#define FILTRO_H
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include "pixel.h"
#include "imagen.h"

typedef enum{FILTRO_INVERTIR, FILTRO_SATURAR, FILTRO_GAMA, FILTRO_BRILLO, FILTRO_CONTRASTE, FILTRO_MEZCLAR, FILTRO_SEPIA, FILTRO_MONOCROMO, FILTRO_TOASTER, FILTRO_VALENCIA} filtro_t;
struct tabla_de_filtros;


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
bool cadena_a_filtro(const char *nombre, filtro_t *filtro);
int numero_de_parametros(filtro_t filtro);
void aplicar_filtro(imagen_t *imagen, filtro_t filtro, int parametro);

#endif