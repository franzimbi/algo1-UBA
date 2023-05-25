#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include <ctype.h>
#include <string.h>



//precondiciones:
//-> nombre con 40 caracteres o menos
//-> cantidad mayor igual a 0
//-> precio positivo y puede tener coma

/*
 typedef struct{
    char nombre[40];
    size_t cantidad;
    double precio;
} producto_t;

typedef struct {
    producto_t productos[100];
    size_t cantidad_productos;
}ticket_t;


bool ticket_agregar(ticket_t *t, const char *producto, float precio)
{
    for(size_t i=0; i<t->cantidad_productos; i++)
    {
        if(!strcmp(t->productos[i].nombre, producto) && t->productos[i].precio == precio)
        {
            t->productos[i].cantidad ++;
            return true;
        }
    }

    t->cantidad_productos++;
    if(t->cantidad_productos >100)  return false;

    t->productos[t->cantidad_productos].cantidad=1;
    strcpy(t->productos[t->cantidad_productos].nombre, producto);
    t->productos[t->cantidad_productos].precio = precio;
    return true;
}

double ticket_total(const ticket_t *t)
{
    double total=0;
    for(size_t i=0; i<t->cantidad_productos; i++)
    {
        total += (t->productos[i].precio) * (t->productos[i].cantidad);
    }
    return total;
}

int main(void)
{
    ticket_t ticket={ {{"yerba", 2, 200},
                       {"leche", 4, 150},
                       {"polenta", 3, 60},
                       {"manzana", 2, 70} }, 4};


    fprintf(stderr, "agregar manzana: %s\n", ticket_agregar(&ticket, "manzana", 70) ? "AGREGADO" : "FALLO");
    fprintf(stderr, "agregar fideos: %s\n", ticket_agregar(&ticket, "fideos", 40) ? "AGREGADO" : "FALLO");

    fprintf(stderr, "total: %.2f\n", ticket_total(&ticket));

    return 0;

} */

typedef struct {
    float *v;
    size_t n;
    double t0;
    int f_m;
} tramo_t;

bool escribir_tramo(const tramo_t *t, FILE *f)
{
    
}