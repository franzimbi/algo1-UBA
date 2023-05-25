//#include "filtro.h"
#include "imagen.h"
//#include "pixel.h"
#include "validacion.h"
#include "procesamiento.h"


//input output filter crop horizontal vertical

int main(int argc, char* argv[])
{
    fprintf(stderr, "validando flags: ");

    argumentos_t* argumentos = validar_flag(argc, argv);
        if(argumentos == NULL)
        {
            fprintf(stderr, "ERROR DE ARGUMENTOS DADOS\n");
            fprintf(stderr, "este programa tiene habilitados los siguientes flags:");
            fprintf(stderr, "-input:\n\t->para seleccionar la imagen ppm o bmp de entrada.\n\t->en su ausencia es stdin\n");
            fprintf(stderr, "-output:\n\t->para seleccionar la imagen ppm o bmp de salida.\n\t->en su ausencia es stdout\n");
            fprintf(stderr, "-crop:\n\t->si se desea recortar la imagen\n\t->seguido de ANCHOxALTO+X0+Y0\n");
            fprintf(stderr, "-horizontal:\n\t->si se desea espejar horizontalmente.\n");
            fprintf(stderr, "-vertical:\n\t->si se desea espejar verticalmente.\n");
            fprintf(stderr, "-filter:\n\t->si se desea aplicar un filtro o varios.\n\t->despues del flag se debe dar el nombre del filtro, y de ser necesario, un parametro posteriormente\n");

            return EXIT_FAILURE;
        }


    fprintf(stderr, "OK\n");
    fprintf(stderr, "leyendo imagen desde input:");
    
    imagen_t * imagen_procesada = leer_input(argumentos);
    if(imagen_procesada==NULL)
    {
        fprintf(stderr, "FALLO EN LA LECTURA DESDE INPUT\n");
        return EXIT_FAILURE;
    }

    fprintf(stderr, "OK\n");
    fprintf(stderr, "recortando y epejando: ");

    if(aplicar_recortes_y_espejamientos(argumentos, imagen_procesada)==false)
    {
        fprintf(stderr, "ERROR\n");
        return EXIT_FAILURE;
    }

    fprintf(stderr, "OK\n");
    fprintf(stderr, "aplicando filtros: ");

    aplicar_filtros(argumentos, imagen_procesada);

    fprintf(stderr, "OK\n");
    fprintf(stderr, "escribiendo imagen en output: ");

    escribir_output(argumentos, imagen_procesada);
    fprintf(stderr, "OK\n");

    fprintf(stderr, "liberando memoria usada:");
    liberar_argumentos(argumentos);
    imagen_destruir(imagen_procesada);

    fprintf(stderr, "OK\n\n");
    
    fprintf(stderr, "CONVERSION EXITOSA!\n\n");

    return EXIT_SUCCESS;
}
