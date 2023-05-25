#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*size_t gcd(int a, int b)
{   
    if(b==0)
        return a;
    
return  gcd(b, a%b); 
} */

size_t gcd(int a, int b)
{   
    if(b==0)
        return a;
    
return  gcd(b, a%b); 
}

int main(void)
{
    printf("%zu\n", gcd(24,16));
    return 0;
}
