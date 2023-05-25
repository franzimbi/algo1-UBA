#ifndef PIXEL_H
#define PIXEL_H

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_ANCHO   1000
#define MAX_ALTO    1000
#define MAX_LENGHT 20



#define MASK_RED 0xFF0000
#define MASK_GREEN 0xFF00
#define MASK_BLUE 0xFF
#define SHIFT_RED 16
#define SHIFT_GREEN 8


typedef uint8_t componente_t;
typedef uint32_t pixel_t;

typedef pixel_t (*funcion_t)(pixel_t, int);

struct colores_tabla{
    char *nombre;
    pixel_t pixel;
};





pixel_t pixel_desde_rgb(componente_t rojo, componente_t verde, componente_t azul);

componente_t pixel_get_rojo(pixel_t p);

componente_t pixel_get_verde(pixel_t p);

componente_t pixel_get_azul(pixel_t p);

void pixel_a_hsv(pixel_t p, short *h, float *s, float *v);

pixel_t pixel_desde_hsv(short h, float s, float v);




pixel_t pixel_desde_nombre(const char *nombre);



#endif
