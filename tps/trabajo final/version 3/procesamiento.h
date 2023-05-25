#ifndef PROCESAMIENTO_H
#define PROCESAMIENTO_H

#include "filtro.h"
#include "imagen.h"
#include <stdlib.h>
#include "validacion.h"

imagen_t *leer_input(argumentos_t* arg);
void aplicar_filtros(argumentos_t * arg, imagen_t * imagen);
bool aplicar_recortes_y_espejamientos(argumentos_t* arg, imagen_t * imagen);
void escribir_output(argumentos_t* arg, imagen_t* imagen);

#endif
