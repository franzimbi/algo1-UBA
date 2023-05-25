#include "entrada.h"



bool analisis_de_parametros(int argc, char *argv[], parametros_t *parametros, tipo_parametro_t orden[]){
    parametros->input_ppm = true;
    parametros->output_ppm = true;
    parametros->horizontal = false;
    parametros->vertical = false;
    parametros->size_orden = 0;    
    parametros->size_filtro = 0;
    parametros->input = NULL;
    parametros->output = NULL;

    for(size_t i=1; i<argc; i++){

        if(!strcmp(argv[i], "-input")){
            if(argc <= i+1){
                fprintf(stderr, "Falta nombre de archivo de entrada\n");
                return false;
            }
            parametros->input_ppm = es_ppm(argv[i+1], "ppm");
            parametros->input = argv[i+1];
            i++;
        }
        else{
            if(!strcmp(argv[i], "-output")){
                if(argc <= i+1){
                    fprintf(stderr, "Falta nombre de archivo de salida\n");
                    return false;
                }
                parametros->output_ppm = es_ppm(argv[i+1], "ppm");
                parametros->output = argv[i+1];
                i++;
            }
            else{
                if(!strcmp(argv[i], "-filter")){
                    int n_params = analisis_de_filtros(argc, argv, i, parametros);
                    if(n_params == -1)
                        return false;      
                    i += n_params+1;
                    orden[parametros->size_orden++] = FILTRO;
                }
                else{
                    if(!strcmp(argv[i], "-crop")){
                        if(argc <= i+1){
                            fprintf(stderr, "Falta parametro de crop\n");
                            return false;
                        }
                        if(!analisis_de_crop(argv[i+1], parametros)){
                            fprintf(stderr, "Error en los parametros de crop\n");
                            return false;
                        }
                        i++;
                        orden[parametros->size_orden++] = CROP;
                        
                    }
                    else{
                        if(!strcmp(argv[i], "-horizontal")){
                            parametros->horizontal = true;
                            orden[parametros->size_orden++] = ESPEJAR_H;
                        }
                        else{
                            if(!strcmp(argv[i], "-vertical")){ 
                                parametros->vertical = true;
                                orden[parametros->size_orden++] = ESPEJAR_V;
                            }
                            else{
                                fprintf(stderr, "Opcion invalida\n");
                                return false;
                            }
                        }
                    }
                }
            }
        }        


    }

    return true;

}




int analisis_de_filtros(int argc, char *argv[], size_t i, parametros_t *parametros){
    
    filtro_t filtro;
    
    if (argc <= i+1)
        return -1;

    if(! cadena_a_filtro(argv[i+1], &filtro)){
        fprintf(stderr, "El filtro %s no es un filtro valido\n", argv[i+1]);
        return -1;
    }

    
    int parametro = 0;
    int n_params = numero_de_parametros(filtro);
    if(n_params == 1) {
        if(argc <= i+2) {
            fprintf(stderr, "El filtro %s lleva un parametro\n", argv[i+1]);
            return -1;
        }

        if(filtro == FILTRO_MEZCLAR)
            parametro = pixel_desde_nombre(argv[i+2]);
        else
            parametro = atoi(argv[i+2]);
    
    }

    int size = parametros->size_filtro;

    parametros->filtros[size].filtro = filtro;

    parametros->filtros[size].param_filtro = parametro;
    parametros->filtros[size].n_param = n_params;
    parametros->size_filtro++;

    return n_params;

}

bool es_ppm(char *fn, char *end){
    if(strlen(fn) <= strlen(end))
        return false;
    return !strcmp(fn + strlen(fn) - strlen(end), end);
}

bool analisis_de_crop(char *parametro_recorte, parametros_t *parametros){
    //crop WxH+X+Y
    char *p;
        
    parametros->ancho = strtol(parametro_recorte, &p, 10);

    if(*p!='x')
        return false;

    parametros->alto = strtol(p+1, &p, 10);
    
    if(*p!='+')
        return false;

    parametros->x0 = strtol(p+1, &p, 10);

    if(*p!='+')
        return false;

    parametros->y0 = strtol(p+1, &p, 10);

    if(parametros->alto*parametros->ancho == 0){
        return false;
    }

    return *p == '\0';
}





imagen_t *entrada(bool es_ppm, char *input){
    imagen_t *imagen;
    if(es_ppm){
        if(input == NULL){  
            imagen=  imagen_leer_PPM_stdin();

        }
        else{  
            FILE *f = fopen(input, "r");
            if(f == NULL) {
                fprintf(stderr, "No se pudo abrir \"%s\"\n", input);
                return NULL;
            }
            imagen=imagen_leer_PPM(f);
            fclose(f);
        }
    }
    else{  
        FILE *f = fopen(input, "r");
        if(f == NULL) {
            fprintf(stderr, "No se pudo abrir \"%s\"\n", input);
            return NULL;
        }

        imagen=imagen_leer_bmp(f);
        fclose(f);
    }    
    return imagen;
}






