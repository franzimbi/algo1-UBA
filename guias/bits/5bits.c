#include <stdio.h>

/*
Escribir un fragmento de código/procedimiento que convierta un número entero sin signo (32 bits) a formato Big Endian, sobre un arreglo de 4 bytes. Imprimir por stdout las representaciones origen y destino.
*/

int * decimal_a_hexa(long nro, int restos[])
{
    int resto=nro;
    int i=0;
    while(resto>=16)
    {
        restos[i]= resto%16;
        resto /=16;
        i++;
    }
    return restos;
}

void imprimir_big_endian(int s[])
{
    for( int i=0; i<4; i++)
    {
            printf("X["%d"]0x%x\n", i, s[i]);
    }
}

int main(void)
{
    long nro = 271590900;
    int s[4];

    s = decimal_a_hexa(nro, s);
    imprimir_big_endian(s);

    return 0;
}
