#include "procesamiento.h"

imagen_t *leer_input(argumentos_t* arg)
{
    imagen_t * imagen = NULL;


    if(arg->input.tipo == STD || arg->input.tipo == PPM)
    {
        
        imagen = imagen_leer_ppm(arg->input.archivo);
            if(imagen==NULL)
                return NULL;
    }

    if(arg->input.tipo == BMP)
    {
        imagen = imagen_leer_BMP(arg->input.archivo);
            if(imagen==NULL)
                return NULL;
    }

    return imagen;
}

void aplicar_filtros(argumentos_t * arg, imagen_t * imagen)
{
    for(size_t i=0; i<arg->cantidad_filtros; i++)
    {
        aplicar_filtro(imagen, arg->filtros[i], arg->parametros[i]);
    }
}

/*static bool aplicar_crop(argumentos_t * arg, imagen_t * imagen)
{   
    imagen_t *recorte = imagen_recortar(imagen, arg->crop.x, arg->crop.y, arg->crop.ancho, arg->crop.alto);
        if(recorte == NULL)
            return false;
    
    imagen_destruir(imagen);
    imagen = recorte;

    arg->crop.encendido = false;

    return true; 
}*/

bool aplicar_recortes_y_espejamientos(argumentos_t* arg, imagen_t * imagen)
{
    for(size_t i=0; i<arg->cantidad_espejados_y_recortes;i++)
    {
        if(arg->orden_espejados_y_recortes[i] == RECORTAR)
        {
            fprintf(stderr, "\naca1\n");
            imagen_t * recorte = imagen_recortar(imagen, arg->crop.x, arg->crop.y, arg->crop.ancho, arg->crop.alto);
            if(recorte==NULL)
                return false;
            
            imagen_destruir(imagen);
            imagen = recorte;
        }
        
        if(arg->orden_espejados_y_recortes[i] == ESPEJAR_V)
            espejar_verticalmente(imagen);

        if(arg->orden_espejados_y_recortes[i] == ESPEJAR_H)
            espejar_horizontalmente(imagen);
    }

    return true;
}

void escribir_output(argumentos_t* arg, imagen_t* imagen)
{
    if(arg->output.tipo == STD || arg->output.tipo == PPM)
    {
        imagen_escribir_ppm(imagen, arg->output.archivo);
            return;
    }

    if(arg->output.tipo == BMP)
    {
        imagen_escribir_BMP(imagen, arg->output.archivo);
            return;
    }
}
