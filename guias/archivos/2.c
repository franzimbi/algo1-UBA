#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char * argv[])
{
    assert(argc == 3);
    int c;
    FILE* fi = fopen(argv[1],"rb");
        if(fi==NULL) return EXIT_FAILURE;

    FILE* fo = fopen(argv[2], "wb");
        if(fo==NULL)
        {
            fclose(fi);
            return EXIT_FAILURE;
        }

    while((c=fgetc(fi))!=EOF)
    {
        fputc(c, fo);
    }

    fclose(fi);
    fclose(fo);

    return EXIT_SUCCESS;
}
