#include "procesamiento.h"






imagen_t *procesamiento(parametros_t *parametros, tipo_parametro_t orden[]){
    
    
    imagen_t *imagen = entrada(parametros->input_ppm, parametros->input);
    imagen_t *recortada;
    if(imagen == NULL)
        return NULL;

    int next_filtro=0;
    for(int i=0; i<parametros->size_orden; i++){
        switch (orden[i]){
        case CROP:
            
            recortada = imagen_recortar(imagen, parametros->x0, parametros->y0, parametros->ancho, parametros->alto);
            if(recortada == NULL)
                return NULL;
            imagen_destruir(imagen);
            imagen = recortada;
            break;
        case ESPEJAR_H:
            
            espejar_horizontalmente(imagen);
            break;
        case ESPEJAR_V:
           
            espejar_verticalmente(imagen);
            break;
        case FILTRO:
            
            aplicar_filtro(imagen, parametros->filtros[next_filtro].filtro, parametros->filtros[next_filtro].param_filtro);
            next_filtro++;
            break;
        default:
            break;
        }
    }

    return imagen;

}