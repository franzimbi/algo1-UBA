#include "validacion.h"

static int validar_extension(char* extension)
{
    size_t tamano = strlen(extension);
    size_t i;

    for(i=0 ; i<tamano; i++)
    {
        if(extension[i]=='.')
            break; //gatito_color.ppm
    }
    if(!strcmp(&extension[i], ".ppm"))
        return PPM;
    if(!strcmp(&extension[i], ".bmp"))
        return BMP;

    return INDEFINIDO;

}

FILE* validar_input(argumentos_t * argumentos)
{
    *tipo = INDEFINIDO;

    if((*tipo = validar_extension(argumentos->input)) == INDEFINIDO)
        return NULL;
    
    if(*tipo == BMP)
    {
        FILE* fi = fopen(argumentos->input, "rb");
        if(fi==NULL)
            return NULL;
    
        return fi;
    }
    if(*tipo == PPM)
    {
        FILE* fi = fopen(argumentos->input, "r");
        if(fi==NULL)
            return NULL;

        return fi;
    }

    return stdin;
}

FILE* validar_output(irgumentos_t * argumentos)
{
    *tipo = INDEFINIDO;

    if((*tipo = validar_extension(argumentos->output)) == INDEFINIDO)
        return NULL;
    
    if(*tipo == BMP)
    {
        FILE* fo = fopen(argumentos->output, "wb");
        if(fo==NULL)
            return NULL;
    
        return fo;
    }
    if(*tipo == PPM)
    {
        FILE* fo = fopen(argumentos->output, "w");
        if(fo==NULL)
            return NULL;

        return fo;
    }
    return stdout;
}
static void extraer_parametros_crop(char* crop, size_t *x, size_t *y, size_t*alto, size_t* ancho)
{

}

    imagen_t * validar_recorte(int argc, char* argv[], FILE* f)
    {
        size_t x, y, alto, ancho;
        for(size_t i=0; i<argc; i++)
        {
            if(!strcmp(argv[i], "-crop"))
            {
                extraer_parametros_crop(&x, &y, &alto, &ancho);

                imagen_t * recorte = imagen_recortar(f, x, y, ancho, alto);
                    if(recorte == NULL)
                        return NULL;
                
                free(f);
                return recorte;
            }
        }
        return NULL;
    }
*/