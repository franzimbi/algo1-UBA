#include "validacion.h"

struct arg{
    char* input;
    char* output;
    char crop[20];
    bool horizontal;
    bool vertical;
    size_t cantidad_filtros;
    filtro_t filtros[5];
    int parametros[5];
};



argumentos_t * validar_flag(int argc, char* argv[])
{
    argumentos_t * argumentos_validados = malloc(sizeof(argumentos_t));
        if(argumentos_validados==NULL)
            return NULL;

    argumentos_validados->cantidad_filtros = 0;
    argumentos_validados->vertical = false;
    argumentos_validados->horizontal = false;

    for(size_t i=0; i<argc; i++)
    {
        if(!strcmp(argv[i], "-input"))
        {
            strcpy(argumentos_validados->input, argv[i+1]);
            i+=1;
            continue;
        }
        if(!strcmp(argv[i], "-output"))
        {
            strcpy(argumentos_validados->output, argv[i+1]);
            i+=1;
            continue;
        }
        if(!strcmp(argv[i], "-crop"))
        {
            strcpy(argumentos_validados->crop, argv[i+1]);
            i+=1;
            continue;
        }
        if(!strcmp(argv[i], "-horizontal"))
        {
            argumentos_validados->horizontal = true;
            continue;
        }
        if(!strcmp(argv[i], "-vertical"))
        {
            argumentos_validados->vertical = true;
            continue;
        }
        if(!strcmp(argv[i], "-filter"))
        {
            if(i+1 > argc) //si esta -filter sin nada despues devuelve null
            {
                free(argumentos_validados);
                return NULL;
            }
            if(cadena_a_filtro(argv[i+1], &argumentos_validados->filtros[argumentos_validados->cantidad_filtros]) == false)  //si el filtro no existe devuelve null
            {   
                free(argumentos_validados);
                fprintf(stderr, "filtro %s invalido\n", argv[i+1]);
                return NULL;
            }
            if(numero_de_parametros(argumentos_validados->filtros[argumentos_validados->cantidad_filtros]) == 1) //tiene parametros?
            {
            
                if(i+1 > argc) // el usuario nos proporciono un parametro mas?
                {
                free(argumentos_validados);
                fprintf(stderr, "parametro no proporcionado\n");
                return NULL;
                }

               if(argumentos_validados->filtros[argumentos_validados->cantidad_filtros] == MEZCLAR)
               {
                argumentos_validados->parametros[argumentos_validados->cantidad_filtros] = pixel_desde_nombre(argv[i+2]);
               }
                else{

                    if(i+2 > argc)
                    {
                    free(argumentos_validados);
                    return NULL;
                    }

                char** endptr=NULL;

                int parametro = strtol(argv[i+2], endptr, 10);
                    if(**endptr != '\0')
                    {
                    free(argumentos_validados);
                    return NULL;
                    }

                argumentos_validados->parametros[argumentos_validados->cantidad_filtros] = parametro;
                argumentos_validados->cantidad_filtros ++;
                }

            i+=1;
            }

        i+=1;
        continue;
        }

        free(argumentos_validados);
        return NULL;
    }

    return argumentos_validados;
}

static int validar_extension(char* extension)
{
    size_t tamano = strlen(extension);
    size_t i;

    for(i=0 ; i<tamano; i++)
    {
        if(extension[i]=='.')
            break; // llega al . de la extension
    }
    if(!strcmp(&extension[i], ".ppm"))
        return PPM;
    if(!strcmp(&extension[i], ".bmp"))
        return BMP;

    return INDEFINIDO;

}

FILE* abrir_input(argumentos_t * argumentos, extension_t *tipo)
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

FILE* abrir_output(argumentos_t * argumentos, extension_t *tipo)
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


