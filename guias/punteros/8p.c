/*Escribir una función que convierta un número que representa una cantidad de segundos, a su equivalente en horas, minutos y segundos, retornando las partes por la interfaz, bool por el nombre, indicando el resultado de la operación, true de ser posible false si no. Realizar las validaciones pertinentes. */

#include <stdio.h>
#include <stdbool.h>

bool de_segundos_hms (int *seg, int *min, int *hrs)
{
    if((*seg)<0)
        return false;

    *hrs = (*seg) / 3600 ;
   *min = ((*seg) % 3600) / 60;
    *seg = ((*seg) % 3600) % 60;

    return true;
}

int main(void)
{
    int segundos= 4805, minutos, horas;


    printf("%s\n", de_segundos_hms(&segundos,&minutos,&horas) ? "true" : "false");
    printf("%dhs %d min %dseg\n", horas, minutos, segundos);

    return 0;
}

