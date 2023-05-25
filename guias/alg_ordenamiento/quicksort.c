#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int *L, int left, int right)
{
    int pivot = left;
    int p_val = L[pivot];

    while (left < right)
    {
        while (L[left] <= p_val)
            left++;
        while (L[right] > p_val)
            right--;
        if (left < right)
            swap(&L[left], &L[right]);
    }
    swap(&L[pivot], &L[right]);
    return right;
}


void quicksort_(int *L, int start, int end)
{
    if (start >= end)
        return;
    int splitPoint = partition(L, start, end);
    quicksort_(L, start, splitPoint - 1);
    quicksort_(L, splitPoint + 1, end);
}


int main(void)
{
    int v[] = {6,5,2,9,1,8,12,6,0,8,19,22};

    for(size_t i=0; i<12; i++)
    {
        printf("%i ", v[i]);
    }
    printf("\n");

    quicksort_(v, 0, 11);

    for(size_t i=0; i<12; i++)
    {
        printf("%i ", v[i]);
    }

    printf("\n");
    
    return 0;
}
