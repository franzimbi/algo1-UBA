#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARRAY 6

 int valor_max(const int nums[], size_t size_array)
 {
 	int max = nums[0];

 	for(int i=1; i<size_array; i++)
 	{
 		if(nums[i]>max)
 			max= nums[i];
 	}
 return max;
 } 

 int main(void)
 {
 	int arreglo[MAX_ARRAY] = {1,20,54,65,87,34};

 	printf("el mayor es: %d\n", valor_max(arreglo, sizeof(arreglo)/4));
 
 return 0;
 }
