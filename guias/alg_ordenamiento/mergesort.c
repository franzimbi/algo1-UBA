#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *merge(int l1[], size_t n1, int l2[], size_t n2) {
    size_t i1, i2;

    int *res = malloc((n1 + n2) * sizeof(int));
    if(res == NULL)
        return NULL;
    size_t i = 0;

    i1 = i2 = 0;
    while(i1 < n1 && i2 < n2) {
        if(l1[i1] < l2[i2]) {
            res[i++] = l1[i1++];
        }
        else
            res[i++] = l2[i2++];
    }

    while(i1 < n1) {
        res[i++] = l1[i1++];
    }

    while(i2 < n2) {
        res[i++] = l2[i2++];
    }

    return res;
}

static int *mergesort_(int l[], size_t n) {
    if(n == 1) {
        int *r = malloc(sizeof(int));
        *r = l[0];
        return r;
    }

    size_t medio = n / 2;
    int *izq = mergesort_(l, medio);
    int *der = mergesort_(l + medio, n - medio);

    int *completo = merge(izq, medio, der, n - medio);

    free(izq);
    free(der);

    return completo;
}

void mergesort2(int l[], size_t n) {
    int *r = mergesort_(l, n);
    memcpy(l, r, n * sizeof(int));
    free(r);
}


int main(void)
{
    int v[] = {6,5,2,9,1,8,12,6,0,8,19,22};

    for(size_t i=0; i<12; i++)
    {
        printf("%i ", v[i]);
    }
    printf("\n");

    mergesort2(v, 12);

    for(size_t i=0; i<12; i++)
    {
        printf("%i ", v[i]);
    }

    printf("\n");
    
    return 0;
}
