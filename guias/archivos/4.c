#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


/* Escriba un programa que cuente la cantidad de líneas de un archivo, si el programa recibe el argumento -l. Opcionalmente, agregue al programa la posibilidad de contar palabras si recibe el argumento -w y bytes si recibe el argumento -c. Si recibe más de un archivo como argumento, imprime los totales. */


int main(int argc, char* argv[])
{
    size_t cantidad=1;
    int c;

    FILE* archivo = fopen(argv[2], "rb");
        if(archivo==NULL) return EXIT_FAILURE;

    if((!strcmp(argv[1], "-l")))
    {
        while(( c=fgetc(archivo) )!=EOF)
        {
            if(c=='\n')
                cantidad++;
        }
    }

    else{
        fprintf(stderr, "%s no disponible\n", argv[1]);
        return EXIT_FAILURE;
    }
    
    printf("%zu: %s\n", cantidad, argv[2]);
    fclose(archivo);
    return EXIT_SUCCESS;

}
