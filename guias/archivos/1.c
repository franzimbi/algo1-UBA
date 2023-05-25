#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


int main(int argc, char *argv[])
{
    assert(argc==3);

    char entrada[30];

    FILE * out = fopen(argv[1], "w");

    fgets(entrada, 30, stdin);
    while(strcmp(entrada, argv[2])!=0)  //con strcmp >= 0 funciona
    {
        fprintf(out, "%s\n", entrada);
        fgets(entrada, 30, stdin);
    }

    fclose(out);

    return EXIT_SUCCESS;
}
