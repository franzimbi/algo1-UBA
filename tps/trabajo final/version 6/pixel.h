#ifndef PIXEL_H
#define PIXEL_H

#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

typedef uint8_t componente_t;
typedef uint32_t pixel_t;

pixel_t pixel_desde_rgb(componente_t rojo, componente_t verde, componente_t azul);
pixel_t pixel_desde_hsv(short h, float s, float v);
componente_t pixel_get_rojo(pixel_t p);
componente_t pixel_get_verde(pixel_t p);
componente_t pixel_get_azul(pixel_t p);
void pixel_a_hsv(pixel_t p, short *h, float *s, float *v);

#endif
