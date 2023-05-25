/*
Una estructura para manejar inventarios que contenga un campo para la descripción del producto (máximo 30 caracteres), un número para el número de parte en el inventario, un punto flotante para el precio, un entero para la cantidad que hay en el almacén y un entero para el lugar donde se almacena.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct
{
    char nombre[30];
    long nro_inventario;
    float precio;
    unsigned long cantidad;
    unsigned int local;
}producto_t;

/*
Una estructura, registro, que nos sirva para mantener un registro de los consumos de un vehículo, como en el último ejercicio de la guía 1. Para ello, debe contener un número para almacenar una cantidad de kilómetros, un número real para almacenar el costo del combustible, un número real para almacenar el dinero utilizado en una recarga, un time_t para almacenar la fecha, un booleano para indicar si se llenó el tanque y un arreglo para almacenar algún comentario.
*/

typedef struct
{
    unsigned long km;
    unsigned long combustible;
    unsigned long dinero;
    time_t fecha;
    bool tanque_lleno;

}registro;

int main(void)
{
    producto_t fideos ={"matarazzo", 23678, 66.5, 5, 3};

    printf("%s\n%ld\n%f\n%lu\n%d\n", fideos.nombre, fideos.nro_inventario, 
    fideos.precio, fideos.cantidad, fideos.local);


   registro fitito ={300000, 50, 200, time(0), false};
    printf("%lu\n%ld\n%lu\n%lu\n%s\n", fitito.km, fitito.combustible, fitito.dinero, 
    fitito.fecha, !fitito.tanque_lleno ? "NO ESTA LLENO" : "LLENO");
   

    return EXIT_SUCCESS;
}
