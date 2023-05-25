#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

size_t fib(size_t n)
{
    if(n==1 || n==0)
        return 1;
    
    return  fib(n-1) + fib(n-2);
}


int main(void)
{
    printf("%zu\n", fib(10));
    return 0;
}

