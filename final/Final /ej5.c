#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

// HACER: implementar la funcion


static int* merge2(const int *a, size_t ia, const int *b, size_t ib, size_t *r_lon)
{
    size_t i1=0, i2=0, i=0;

    int *r = malloc((ia+ib)*sizeof(int));
    if(r==NULL)
        return NULL;

    while(i1<ia && i2<ib)
    {
         if(a[i1] < b[i2]) {
            r[i++] = a[i1++];
        }
        else
            r[i++] = b[i2++];
    }

    while(i1<ia)
        r[i++] = a[i1++];

    while(i2<ib)
        r[i++] = b[i2++];
    
    *r_lon = i;
    return r;
}

void merge3(const int a[], size_t na, const int b[], size_t nb, const int c[], size_t nc, int r[])
{
    size_t i1=0, i2=0,i=0;
    size_t nr=0;

    
    int* r2 = merge2(a,na,b,nb,&nr);


    while(i2<nc && i1<nr)
    {
       if(r2[i1] < c[i2])
            r[i++] = r2[i1++];

        else
            r[i++] = c[i2++];
    }

     while(i1 < nr) {
        r[i++] = r2[i1++];
    }

    while(i2 < nc) {
        r[i++] = c[i2++];
    }

    free(r2);
}

int main(void) {
    int a[] = {1, 4, 7};
    int b[] = {2, 5, 8};
    int c[] = {3, 6, 9};
    int r[9];

    merge3(a, 3, b, 3, c, 3, r);

    int esperado[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i = 0; i < 9; i++) {
        //fprintf(stderr, "%i", r[i]);
        assert(r[i] == esperado[i]);
    }

    // OPCIONAL: Pruebas adicionales. Sugerencias:
    // - Listas con numeros repetidos
    // - Una lista con todos sus numeros menores a las otras dos
    // - Una lista con todos sus numeros mayores a las otras dos

    printf("%s: OK\n", __FILE__);
    return 0;
}
