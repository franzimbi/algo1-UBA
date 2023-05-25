#include "validacion.h"

static int validar_extension(char* extension)
{
    size_t tamano = strlen(extension);
    size_t i;

    for(i=tamano ; i>0; i--)
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
    argumentos_t * argumentos_validados = malloc(sizeof(argumentos_t));//pide memoria para guardar los argumentos correctamente validados
        if(argumentos_validados==NULL)
            return NULL;
    
    //inicializacion de los argumentos
    argumentos_validados->cantidad_filtros = 0;
    argumentos_validados->cantidad_espejados_y_recortes = 0;
    argumentos_validados->crop.encendido = false;


//se recorre todo argc en busca de todos los flags, validandolos
    for(size_t i=1; i<argc; i++)
    {        
        if(!strcmp(argv[i], "-input"))
        {
            if(i+1 >= argc) 
            {
                fprintf(stderr, "\n\nFLAG INPUT SIN PARAMETRO\n\n");
                free(argumentos_validados);
                fclose(argumentos_validados->input.archivo);
                fclose(argumentos_validados->output.archivo);
                return NULL;
            }

            if(abrir_input(argumentos_validados, argv[i+1]) == false)
            {
                fprintf(stderr, "\n\nARCHIVO INPUT INEXISTENTE O DE TIPO INCORRECTO\n\n");
                free(argumentos_validados);
                fclose(argumentos_validados->input.archivo);
                fclose(argumentos_validados->output.archivo);
                return NULL;
            }

            i+=1;
            continue;
        }
        if(!strcmp(argv[i], "-output"))
        {
            if(i+1 >= argc) 
            {
                fprintf(stderr, "\n\nFLAG OUTPUT SIN PARAMETRO\n\n");
                free(argumentos_validados);
                fclose(argumentos_validados->input.archivo);
                fclose(argumentos_validados->output.archivo);
                return NULL;
            }

            if(abrir_output(argumentos_validados, argv[i+1]) == false)
            {
                fprintf(stderr, "\n\nARCHIVO OUTPUT DE TIPO INCORRECTO\n\n");
                free(argumentos_validados);
                fclose(argumentos_validados->input.archivo);
                fclose(argumentos_validados->output.archivo);
                return NULL;
            } 
            i+=1;
            continue;
        }
        if(!strcmp(argv[i], "-crop"))
        {
            if(i+1 >= argc) 
            {
                fprintf(stderr, "\n\nFLAG CROP SIN PARAMETRO\n\n");
                free(argumentos_validados);
                fclose(argumentos_validados->input.archivo);
                fclose(argumentos_validados->output.archivo);
                return NULL;
            }

            if(crop(argumentos_validados, argv[i+1])==false)
            {
                fprintf(stderr, "\n\nPARAMETROS DE RECORTE INVALIDOS\n\n");
                free(argumentos_validados);
                fclose(argumentos_validados->input.archivo);
                fclose(argumentos_validados->output.archivo);
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
            if(i+1 >= argc) //si esta -filter sin nada despues devuelve null
            {
                fprintf(stderr, "\n\nFLAG DE FILTROS SIN PARAMETRO\n\n");
                free(argumentos_validados);
                fclose(argumentos_validados->input.archivo);
                fclose(argumentos_validados->output.archivo);
                return NULL;
            }
            if(cadena_a_filtro(argv[i+1], &argumentos_validados->filtros[argumentos_validados->cantidad_filtros]) == false)  //si el filtro no existe devuelve null
            {   
                fprintf(stderr, "\n\nEL FILTRO //%s// NO EXISTE\n\n", argv[i+1]);
                free(argumentos_validados);
                fclose(argumentos_validados->input.archivo);
                fclose(argumentos_validados->output.archivo);
                return NULL;
            }
            if(numero_de_parametros(argumentos_validados->filtros[argumentos_validados->cantidad_filtros]) == 1) //tiene parametros?
            {
            
                if(i+2 >= argc) // el usuario no proporciona un parametro
                {
                fprintf(stderr, "\n\nEL FILTRO //%s// NECESITA UN PARAMETRO\n\n", argv[i+1]);
                free(argumentos_validados);
                fclose(argumentos_validados->input.archivo);
                fclose(argumentos_validados->output.archivo);
                return NULL;
                }

               if(argumentos_validados->filtros[argumentos_validados->cantidad_filtros] == MEZCLAR)
               {
                argumentos_validados->parametros[argumentos_validados->cantidad_filtros] = pixel_desde_nombre(argv[i+2]);
               }
                else{

                char* endptr;

                int parametro = strtol(argv[i+2], &endptr, 10);
                    if(*endptr != '\0')
                    {
                    fprintf(stderr, "\nPARAMETRO DEL FILTRO //%s// INVALIDO\n\n", argv[i+1]);
                    free(argumentos_validados);
                    fclose(argumentos_validados->input.archivo);
                    fclose(argumentos_validados->output.archivo);
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
        fprintf(stderr, "\nEL FLAG //%s// NO ES VALIDO\n\n", argv[i]);
        free(argumentos_validados);
        fclose(argumentos_validados->input.archivo);
        fclose(argumentos_validados->output.archivo);
        return NULL;
    }

    return argumentos_validados;
}

void liberar_argumentos(argumentos_t* argumentos)
{
    free(argumentos);
}
