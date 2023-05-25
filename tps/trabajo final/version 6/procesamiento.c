#include "procesamiento.h"

imagen_t *leer_input(argumentos_t* arg)
{
    imagen_t * imagen = NULL;

    if(arg->input.tipo == STD )
    {
        imagen = imagen_leer_ppm(stdin);
            if(imagen==NULL)
                return NULL;
    }

    if(arg->input.tipo == PPM)
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

    fclose(arg->input.archivo);
    return imagen;
}

void aplicar_filtros(argumentos_t * arg, imagen_t ** imagen)
{
    for(size_t i=0; i<arg->cantidad_filtros; i++)
    {
        aplicar_filtro(*imagen, arg->filtros[i], arg->parametros[i]);
    }
}

bool aplicar_recortes_y_espejamientos(argumentos_t* arg, imagen_t ** imagen)
{
    imagen_t* recorte;
    for(size_t i=0; i<arg->cantidad_espejados_y_recortes;i++)
    {
        if(arg->orden_espejados_y_recortes[i] == RECORTAR)
        {
            recorte = imagen_recortar(*imagen, arg->crop.x, arg->crop.y, arg->crop.ancho, arg->crop.alto);
            if(recorte == NULL)
                return NULL;

            imagen_destruir(*imagen);
            *imagen = recorte;
        }
        
        if(arg->orden_espejados_y_recortes[i] == ESPEJAR_V)
            espejar_verticalmente(*imagen);

        if(arg->orden_espejados_y_recortes[i] == ESPEJAR_H)
            espejar_horizontalmente(*imagen);
    }
    return true;
}

void escribir_output(argumentos_t* arg, imagen_t** imagen)
{
    if(arg->output.tipo == STD)
    {
        imagen_escribir_ppm(*imagen, stdout);
    }
    if(arg->output.tipo == PPM)
    {
        imagen_escribir_ppm(*imagen, arg->output.archivo);
    }

    if(arg->output.tipo == BMP)
    {
        imagen_escribir_BMP(*imagen, arg->output.archivo);
    }
    fclose(arg->output.archivo);
}
