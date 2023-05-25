#include <stdio.h>

void completar_con_ceros(int *arreglo, size_t tamano)
{
    for(int i=0; i<tamano;i++)
    {
        *(arreglo+i) = 0;
    }
}

void completar_con_unos(int *arreglo, size_t tamano)
{
    for(int i=0; i<tamano;i++)
    {
        *(arreglo+i) = 1;
    }
}

void suma_de_arreglo(int *arreglo, size_t tamano, int *suma)
{
    for(int i=0; i<tamano;i++)
    {
       *suma += *(arreglo+i);
    }
}

void maximo_del_arreglo(int *arreglo, size_t tamano, int *maximo)
{
    *maximo = *arreglo;
    for(int i=1; i<tamano;i++)
    {
       if(*(arreglo+i)> *maximo)
        *maximo = *(arreglo+i);
    }
}

void dif_finita_1er_orden(int *arreglo, size_t tamano)
{
    for(int i=0; i<tamano;i++)
    {
        if(i==(tamano -1))
            break;
        *(arreglo + i) = *(arreglo + i+1) - *(arreglo + i); //*(v + 1) = *(v + 2) - *(v + 1)
    }
}
int main(void)
{
    int arreglo[10]={1,35,3,40,5,6,94,8,10,9};
    int suma, maximo;

    for(int i=0; i<(sizeof(arreglo))/4; i++)
    {
        printf("%d  ", arreglo[i]);
    }
    printf("\n");

   completar_con_ceros(arreglo, (sizeof(arreglo))/4);

    for(int i=0; i<(sizeof(arreglo))/4; i++)
    {
        printf("%d  ", arreglo[i]);
    }
    printf("\n");

    completar_con_unos(arreglo,(sizeof(arreglo))/4);

      for(int i=0; i<(sizeof(arreglo))/4; i++)
    {
        printf("%d  ", arreglo[i]);
    }
    printf("\n"); 

    suma_de_arreglo(arreglo, (sizeof(arreglo))/4, &suma);
    printf("%d\n", suma); 

    maximo_del_arreglo(arreglo, (sizeof(arreglo))/4, &maximo);
    printf("%d\n", maximo); 

    dif_finita_1er_orden(arreglo, (sizeof(arreglo))/4);

     for(int i=0; i<(sizeof(arreglo))/4; i++)
    {
        printf("%d  ", arreglo[i]);
    }
    printf("\n");

    return 0;
}
