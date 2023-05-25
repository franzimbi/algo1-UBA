#include <stdio.h>

typedef enum{FALSE = 0,
             TRUE = 1
            } bool;

int main(void)
{
    bool a=FALSE, b= TRUE;

    printf("a es:%d, b es:%d\n", a,b);

    return 0; 
}
