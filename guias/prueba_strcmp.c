#include <stdio.h>
#include <string.h>

int main (void)
{
    char s1[]="hola";
    char s2[]="hola ";
    printf("%i\n", strcmp(s1,s2));
    return 0;
}