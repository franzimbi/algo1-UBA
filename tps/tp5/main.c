#include <stdio.h>
#include <stdlib.h>
#include "pixel.h"
#include "imagen.h"
#include "endianess.h"

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        fprintf(stderr, "error en la cantidad de parametros\n");
        return EXIT_FAILURE;
    }

    fprintf(stderr, "parametros correctos\n");

    FILE * fi = fopen(argv[1], "r");
    if(fi ==NULL)
    {
        fprintf(stderr, "error al abrir el archivo %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    FILE * fo = fopen(argv[2], "wb");
    if(fo==NULL)
    {
        fprintf(stderr, "error al crear el archivo %s\n", argv[2]);
        fclose(fi);
        return EXIT_FAILURE;
    }

    fprintf(stderr, "apertura y creacion de archivo bmp confirmada\n");

    fprintf(stderr, "leyendo imagen ppm... ");
    imagen_t * archivo_ppm = imagen_leer_ppm(fi);
    fprintf(stderr, "OK\n");

    fprintf(stderr, "escribiendo imagen bmp... ");
    imagen_escribir_BMP(archivo_ppm, fo);
    fprintf(stderr, "OK\n");

    fprintf(stderr, "cerrando archvios y liberando memoria...");
    fclose(fi);
    fclose(fo);
    imagen_destruir(archivo_ppm);
    fprintf(stderr, "OK\n");

    fprintf(stderr, "conversion exitosa!\n");

    return EXIT_SUCCESS;
}
