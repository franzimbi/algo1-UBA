#include <stdio.h>
#include <stdint.h>


typedef uint8_t pixel_t;

typedef struct {
    pixel_t **lienzo;
    size_t ancho, alto;
} imagen_t;


void imagen_destruir(imagen_t *imagen);
imagen_t *imagen_leer_stdin();
void imagen_escribir(const imagen_t *imagen);
imagen_t *imagen_recortar(const imagen_t *imagen, size_t x0, size_t y0, size_t ancho, size_t alto);
imagen_t *imagen_clonar(const imagen_t *imagen);


int main(void) {
    fprintf(stderr, "Leyendo imagen...");
    imagen_t *imagen_original = imagen_leer_stdin();
    if(imagen_original == NULL) {
        fprintf(stderr, "\nERROR: No se pudo leer imagen!\n");
        return 1;
    }
    fprintf(stderr, " OK!\n");

    fprintf(stderr, "Clonando imagen...");
    imagen_t *imagen_copia = imagen_clonar(imagen_original);
    if(imagen_copia == NULL) {
        imagen_destruir(imagen_original);
        fprintf(stderr, "\nERROR: No se pudo clonar imagen!\n");
        return 1;
    }
    fprintf(stderr, " OK!\n");

    fprintf(stderr, "Destruyendo imagen original...");
    imagen_destruir(imagen_original);
    fprintf(stderr, " OK!\n");

    fprintf(stderr, "Recortando imagen...");
    imagen_t *imagen_recortada = imagen_recortar(imagen_copia, 300, 100, 330, 300);
    if(imagen_recortada == NULL) {
        imagen_destruir(imagen_copia);
        fprintf(stderr, "\nERROR: No se pudo recortar la imagen.\n");
        return 1;
    }
    fprintf(stderr, " OK!\n");

    fprintf(stderr, "Destruyendo imagen de copia...");
    imagen_destruir(imagen_copia);
    fprintf(stderr, " OK!\n");

    fprintf(stderr, "Escribiendo imagen...");
    imagen_escribir(imagen_recortada);
    fprintf(stderr, " OK!\n");

    fprintf(stderr, "Recortando imagen para que falle...");
    if(imagen_recortar(imagen_recortada, 100, 300, 20, 20) != NULL) {
        imagen_destruir(imagen_recortada);
        fprintf(stderr, "Imagen de tamano cero no vale NULL\n");
        return 1;
    }
    fprintf(stderr, " OK!\n");

    fprintf(stderr, "Destruyendo imagen recortada...");
    imagen_destruir(imagen_recortada);
    fprintf(stderr, " OK!\n");

    fprintf(stderr, "Pasaron todos los tests!\nComprobá con Valgrind que no haya pérdidas de memoria\n");

    return 0;
}
