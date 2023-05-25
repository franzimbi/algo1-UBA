#include <stdio.h>

int hsASeg(int x){

	return x*3600;
}

int minASeg(int x){

	return x*60;
}

int main(void){

int horas, minutos, segundos;
int totalSegundos;

	printf("horas?\n");
	scanf("%d", &horas);

	printf("minutos?\n");
	scanf("%d", &minutos);
	
	printf("segundos?\n");
	scanf("%d", &segundos);

totalSegundos = hsASeg(horas) + minASeg(minutos) + segundos;

printf("%d segundos\n", totalSegundos);

return 0;
}

