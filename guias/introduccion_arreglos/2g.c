#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAXSTEEL 15
#define IRONMAN 12
#define FLASH 20


int main(void)
{
	int cadena[MAXSTEEL];
	float temp_mensuales [IRONMAN];
	char temp[FLASH];

	for(int i=0; i<MAXSTEEL; i++)//a
	{
		cadena[i] = 0;

	}

	for(int i=0; i<MAXSTEEL; i++)//b
	{
		cadena[i] += 1;
	}


	for(int i=0; i<IRONMAN; i++)//c
	{
		fgets(temp, FLASH, stdin);
		temp_mensuales[i]= atof(temp);	
		pritf("%f\t", temp_mensuales[i]);	
	}
	puts("%\n");


return 0;
}

