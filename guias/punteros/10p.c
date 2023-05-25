/*plementar una función que reciba 2 vectores y sus longitudes, y copie el contenido de uno en el otro, usando el siguiente prototipo y notación de punteros en la implementación, la función debe devolver true de poder realizar la operación false en caso contrario*/

#include <stdio.h>
#include <stdbool.h>

#define MAX 10
bool veccpy(double * dest, size_t ldest, const double * orig, size_t lorig)
{
    int i;
    if(ldest<lorig)
        return false;
    
    for(i=0 ; i<lorig; i++)
    {
        *(dest+i) = *(orig+i);
    }


    return true;
}

int main(void)
{
    double a1[MAX]={1,2,3,4,5,6,7,8,9,10}, a2[MAX];

    for(int i=0; i<MAX; i++)
        printf("%f ", a1[i]);
    puts("\n");

    for(int i=0; i<MAX; i++)
        printf("%f ", a2[i]);
    puts("\n");

    printf("%s\n", veccpy(a2, (sizeof(a2))/8, a1, (sizeof(a1))/8) ? "True" : "False");

    for(int i=0; i<MAX; i++)
        printf("%f ", a2[i]);
    puts("\n");

    return 0;
}