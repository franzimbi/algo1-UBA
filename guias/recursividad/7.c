#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

size_t cantidad_letra(char* a, size_t n, char c)
{
    if(n==0)
        return 0;
    
    if(n==1)
       return a[0]== 'c' ? 1 : 0;


    return cantidad_letra(a, n-1, c) + (a[n] == c ? 1:0);
}

bool hay_mas_A_que_E(char* a)
{
    return cantidad_letra(a, strlen(a), 'a') > cantidad_letra(a, strlen(a), 'e') ? true : false;
}
int main(void)
{
    char v[]="hola como eeestas?";
    
    if(hay_mas_A_que_E(v)==true)
        printf("hay mas A\n");
    else 
        printf("hay mas E\n");

    return 0;
}

