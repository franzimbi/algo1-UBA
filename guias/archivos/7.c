#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE* archivo = fopen("ejercicio7.bin", "wb");

    for(size_t i=0; i<=1000; i++)
    {
        int nro=i;
        fwrite(&nro, sizeof(int), 1, archivo);
    }
    fclose(archivo);

    return EXIT_SUCCESS;
}