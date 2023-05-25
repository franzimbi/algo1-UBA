#include <stdio.h>
#include <stdlib.h>

typedef enum {ST_OK = 0, ST_ERR_VALOR_NEGATIVO = 1, ST_ERR_VALOR_NULO = 2, ST_ERR_NO_NRO = 3} status_t;

int main(void)
{
    char s[100];
    char* ps;
    long nro;

    fgets(s, 100,stdin);
    nro = strtol(s, &ps, 10);
    
    if(nro>0)
        puts("gracias, vuelva pronto.\n");
        printf("%d\n", *ps);
        return ST_OK;

    if(nro ==0)
        return ST_ERR_VALOR_NULO;
    
    if(nro<0)
        return ST_ERR_VALOR_NEGATIVO;
}
