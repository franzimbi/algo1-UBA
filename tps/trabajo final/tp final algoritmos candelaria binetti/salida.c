#include "salida.h"


void salida(bool es_ppm, char *output, imagen_t *imagen){
    if(es_ppm){
        if(output == NULL){  
            imagen_escribir_PPM_stdout(imagen);
        }
        else{   
            FILE *f = fopen(output, "wb");
            if(f == NULL) {
                fprintf(stderr, "No se pudo abrir \"%s\"\n", output);
                return;
            }
            imagen_escribir_PPM(imagen, f);
            fclose(f);
        }

    }
    else{   
        FILE *f = fopen(output, "wb");
        if(f == NULL) {
            fprintf(stderr, "No se pudo abrir \"%s\"\n", output);
            return;
        }
        imagen_escribir_BMP(imagen, f);
        fclose(f);
    }
}