#ifndef VALIDACION_H
#define VALIDACION_H

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "filtro.h"

typedef enum{STD=0, PPM=1, BMP=2, INDEFINIDO=3}extension_t;
typedef enum{RECORTAR=0, ESPEJAR_H=1, ESPEJAR_V=2}orden_t;


typedef struct {
    size_t ancho;
    size_t alto;
    size_t x;
    size_t y;
    bool encendido;
}crop_t;

typedef struct {
    extension_t tipo;
    FILE* archivo;
}archivo_t;

typedef struct {
    archivo_t input;
    archivo_t output;
    crop_t crop;
    orden_t orden_espejados_y_recortes[6];
    size_t cantidad_espejados_y_recortes;
    size_t cantidad_filtros;
    filtro_t filtros[5];
    int parametros[5];
}argumentos_t;


argumentos_t * validar_flag(int argc, char* argv[]);
void liberar_argumentos(argumentos_t* argumentos);

#endif
