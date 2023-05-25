#include<stdio.h>
#include <string.h>
#include <stdbool.h>
#include "filtro.h"
#include "imagen.h"
#include "procesamiento.h"
#include "pixel.h"
#include "entrada.h"






int main(int argc, char *argv[]){

    parametros_t parametros;
    tipo_parametro_t orden[MAX];
    
    if(!analisis_de_parametros(argc, argv, &parametros, orden))
        return 1;

    imagen_t *imagen = procesamiento(&parametros, orden);
    if (imagen == NULL)
        return 1;
    
    salida(parametros.output_ppm, parametros.output, imagen);
    free(parametros.input);
    free(parametros.output);
    imagen_destruir(imagen);

    
    return 0;
}
