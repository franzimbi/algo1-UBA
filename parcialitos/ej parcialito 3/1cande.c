#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include <ctype.h>
#include <string.h>

/* precondiciones:
-> nombre con 40 caracteres o menos
-> cantidad mayor igual a 0
-> precio positivo y puede tener coma
*/
 struct producto{
    char nombre[40];
    size_t cantidad;
    double precio;
};

//typedef enum{YERBA, MANZANA, LECHE, VIDA, POLENTA} productos_t;

const struct producto lista[]={ {"yerba", 0, 200.0},
                                {"manzana", 0, 300.0},
                                {"leche", 0, 200.50},
                                {"vida", 0, 2.50},
                                {"polenta", 0, 2120.00}
};


double ticket_total(const ticket_t *t)
{

}
