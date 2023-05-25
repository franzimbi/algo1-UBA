#include "validacion.h"

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

static bool abrir_input(argumentos_t * argumentos, char* archivo)
{   
    extension_t tipo = INDEFINIDO;

    if(!strcmp(archivo, "stdin")){
        argumentos->input.archivo = stdin;
        argumentos->input.tipo = STD;

        return true;
    }

    tipo = validar_extension(archivo);
    
    if(tipo == BMP)
    {
        FILE* fi = fopen(archivo, "rb");
        if(fi==NULL)
            return NULL;

        argumentos->input.archivo = fi;
        argumentos->input.tipo = tipo;

        return true;
    }

    if(tipo == PPM)
    {
        FILE* fi = fopen(archivo, "r");
        if(fi==NULL)
            return NULL;
        
        argumentos->input.archivo = fi;
        argumentos->input.tipo = tipo;

        return true;
    }

    return false;
}

static bool abrir_output(argumentos_t * argumentos, char* archivo)
{
    extension_t tipo = INDEFINIDO;

    if(!strcmp(archivo, "stdout")){
        argumentos->output.archivo = stdout;
        argumentos->output.tipo = STD;

        return true;
    }

    tipo = validar_extension(archivo);
    
    if(tipo == BMP)
    {
        FILE* fo = fopen(archivo, "wb");
        if(fo==NULL)
            return NULL;
    
        argumentos->output.archivo = fo;
        argumentos->output.tipo = tipo;

        return true;
    }
    if(tipo == PPM)
    {
        FILE* fo = fopen(archivo, "w");
        if(fo==NULL)
            return NULL;

        argumentos->output.archivo = fo;
        argumentos->output.tipo = tipo;

        return true;
    }
    return false;
}


static bool crop(argumentos_t *argumentos, char* crop){
    char *endptr;

    argumentos->crop.ancho = strtol(crop, &endptr,10);
    if (*endptr != 'x' && *endptr != 'X')
    {
        return false; 
    } 


    argumentos->crop.alto = strtol(endptr + 1, &endptr ,10);
    if (*endptr != '+')
    {
        return false; 
    }


    argumentos->crop.x = strtol(endptr + 1, &endptr ,10);
    if (*endptr != '+')
    {
        return false;
    }

    argumentos->crop.y = strtol(endptr + 1, &endptr ,10);
    if (*endptr != '\0')
    {
        return false; 
    }

    argumentos->crop.encendido = true;

    return true;
}

argumentos_t * validar_flag(int argc, char* argv[])
{
    argumentos_t * argumentos_validados = malloc(sizeof(argumentos_t));
        if(argumentos_validados==NULL)
            return NULL;

    
    argumentos_validados->cantidad_filtros = 0;
    argumentos_validados->cantidad_espejados_y_recortes = 0;

    argumentos_validados->crop.encendido = false;

    for(size_t i=1; i<argc; i++)
    {
        
        if(!strcmp(argv[i], "-input"))
        {

            if(abrir_input(argumentos_validados, argv[i+1]) == false)
            {
                free(argumentos_validados);
                return NULL;
            }

            i+=1;
            continue;
        }
        if(!strcmp(argv[i], "-output"))
        {
            if(abrir_output(argumentos_validados, argv[i+1]) == false)
            {
                free(argumentos_validados);
                return NULL;
            } 
            i+=1;
            continue;
        }
        if(!strcmp(argv[i], "-crop"))
        {
            if(crop(argumentos_validados, argv[i+1])==false)
            {
                free(argumentos_validados);
                return NULL;
            }
            
            argumentos_validados->orden_espejados_y_recortes[argumentos_validados->cantidad_espejados_y_recortes] = RECORTAR;
            argumentos_validados->cantidad_espejados_y_recortes++;

            i+=1;
            continue;
        }
        if(!strcmp(argv[i], "-horizontal"))
        {
            argumentos_validados->orden_espejados_y_recortes[argumentos_validados->cantidad_espejados_y_recortes] = ESPEJAR_H;
            argumentos_validados->cantidad_espejados_y_recortes++;
            continue;
        }

        if(!strcmp(argv[i], "-vertical"))
        {
            argumentos_validados->orden_espejados_y_recortes[argumentos_validados->cantidad_espejados_y_recortes] = ESPEJAR_V;
            argumentos_validados->cantidad_espejados_y_recortes++;
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
                return NULL;
            }
            if(numero_de_parametros(argumentos_validados->filtros[argumentos_validados->cantidad_filtros]) == 1) //tiene parametros?
            {
            
                if(i+2 > argc) // el usuario no proporciona un parametro
                {
                free(argumentos_validados);
                return NULL;
                }

               if(argumentos_validados->filtros[argumentos_validados->cantidad_filtros] == MEZCLAR)
               {
                argumentos_validados->parametros[argumentos_validados->cantidad_filtros] = pixel_desde_nombre(argv[i+2]);
               }
                else{

                char** endptr=NULL;

                int parametro = strtol(argv[i+2], endptr, 10);
                    if(**endptr != '\0')
                    {
                    free(argumentos_validados);
                    return NULL;
                    }

                argumentos_validados->parametros[argumentos_validados->cantidad_filtros] = parametro;
                }
            i+=1;
            }

        argumentos_validados->cantidad_filtros ++;
        i+=1;
        continue;
        }

        free(argumentos_validados);
        return NULL;
    }

    return argumentos_validados;
}

void liberar_argumentos(argumentos_t* argumentos)
{
    free(argumentos);
}
