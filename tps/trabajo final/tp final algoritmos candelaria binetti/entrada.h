#ifndef ENTRADA_H
#define ENTRADA_H

#include <string.h>
#include <stdbool.h>
#include "filtro.h"
#include"imagen.h"


#define MAX 50

typedef enum {CROP, ESPEJAR_H, ESPEJAR_V, FILTRO} tipo_parametro_t;


typedef struct filtro{
    filtro_t filtro;
    int param_filtro, n_param;
} filtro_aux;

typedef struct parametros{
    bool input_ppm, output_ppm, horizontal, vertical;
    int ancho, alto, x0, y0;
    int size_orden, size_filtro;
    char *input, *output;
    filtro_aux filtros[MAX];
} parametros_t;



bool analisis_de_parametros(int argc, char *argv[], parametros_t *parametros, tipo_parametro_t orden[]);
int analisis_de_filtros(int argc, char *argv[], size_t i, parametros_t *parametros);
bool es_ppm(char *fn, char *end);
bool analisis_de_crop(char *parametro_recorte, parametros_t *parametros);
imagen_t *entrada(bool es_ppm, char *input);
imagen_t *procesamiento(parametros_t *parametros, tipo_parametro_t orden[]);
void salida(bool es_ppm, char *output, imagen_t *imagen);

#endif
