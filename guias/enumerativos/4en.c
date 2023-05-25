#include <stdio.h>
#include <stdlib.h>

typedef enum {ENERO=1, FEBRERO=2, MARZO=3, ABRIL=4, 
              MAYO=5, JUNIO=6, JULIO=7, AGOSTO=8, 
              SEPTIEMBRE=9, OCTUBRE=10, NOVIEMBRE=11, 
              DICIEMBRE=12} mes_t;

int main (void)
{
    char m[][11] ={"0", "enero", "febrero", "marzo", "abril", "mayo", "junio", "julio", "agosto" , "septiembre", "octubre", "noviembre", "diciembre"};
    char buffer[15];
    mes_t mes;

    mes = atoi(fgets(buffer, 15, stdin));

    printf("el %d corresponde al mes: %s\n", mes, m[mes]);

    return EXIT_SUCCESS;
}
