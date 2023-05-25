#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

void escribir_sucursal(char* nombre,float lat, float lon, FILE* archivo)
{
   u_int8_t N = strlen(nombre);

   fwrite(&N, sizeof(u_int8_t), 1, archivo);
   fwrite(nombre, sizeof(char), N, archivo);
   fwrite(&lat, sizeof(float), 1, archivo);
   fwrite(&lon, sizeof(float), 1, archivo);

}

void leer_sucursal(char* nombre, float* lat, float*lon, FILE* archivo)
{
    uint8_t tamano;
    char nombre_leido[32];
    float lat_aux, lon_aux;

    fread(&tamano, sizeof(uint8_t), 1, archivo);
    fread(nombre_leido, sizeof(char), tamano, archivo);
    nombre_leido[tamano] ='\0';
    strcpy(nombre, nombre_leido);
    fread(&lat_aux, sizeof(float),1,archivo);
    fread(&lon_aux, sizeof(float),1,archivo);

    *lat = lat_aux;
    *lon = lon_aux;
}

/* HACER:

Escribir una funcion que recibe un archivo previamente abierto y los datos de una sucursal,
y escribe en el archivo los datos con el formato descripto.

Escribir una funcion que recibe un archivo previamente abierto, lee los datos de una sucursal
y los devuelve (ya sea por el valor de retorno o mediante los parametros).

*/

int main(void) {
    char *nombre = "Caballito 2";
    char nombre2[32]= {0};
    float lat2, lon2;
    float  lat = -45.6145096f, lon = -60.4431307f;

    char *nombre_archivo = "sucursal.bin";


   FILE* fo=fopen(nombre_archivo, "wb");
   if(fo==NULL)
    return EXIT_FAILURE;

    escribir_sucursal(nombre,lat,lon,fo);

    fclose(fo);

     FILE* fi=fopen(nombre_archivo, "rb");
   if(fo==NULL)
    return EXIT_FAILURE;

    leer_sucursal(nombre2, &lat2, &lon2, fi);

    fclose(fi);

    fprintf(stderr, "%f, %f\n", lat2, lon2);

    fprintf(stderr, "%s\n", nombre2);



    // PRUEBA:
    // - abrir el archivo en modo escritura y escribir en el mismo los datos de la sucursal
    // - abrir el archivo en modo lectura y leer del mismo los datos previamente escritos
    // - verificar con assert() que los datos leidos son correctos

    printf("%s: OK\n", __FILE__);
    return 0;
}
