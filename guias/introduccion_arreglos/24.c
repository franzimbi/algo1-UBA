#include <stdio.h>
#include <stdlib.h>

// 1000 - 500 - 200 - 100 - 50 - 20 - 10 - 5

void cantidad_billetes_minima (unsigned long cash)
{
	unsigned long cant_mil=0, cant_quin=0, cant_dos=0, cant_cien=0, cant_cincu=0, 
	cant_veint=0, cant_diez=0, cant_cinco=0;
	
	unsigned long resto=0;

	resto = cash;

	if(cash>=1000){

		cant_mil = cash/1000;
		resto = cash%1000;
	}

	if(resto>=500){

		cant_quin = resto/500;
		resto %= 500;
	}
	
	if(resto>=200){

		cant_dos = resto/200;
		resto %= 200;
	}
	
	if(resto>=100){

		cant_cien = resto/100;
		resto %= 100;
	}
	
	if(resto>=50){

		cant_cincu = resto/50;
		resto %= 50;
	}

	if(resto>=20){

		cant_veint = resto/20;
		resto %= 20;
	}
	
	if(resto>=10){

		cant_diez = resto/10;
		resto %= 10;
}

	if(resto>=5){

		cant_cinco = resto/5;
		resto %= 5;
	}

	printf("son %lu billetes de 1000\n", cant_mil);
	printf("son %lu billetes de 500\n", cant_quin);
	printf("son %lu billetes de 200\n", cant_dos);
	printf("son %lu billetes de 100\n", cant_cien);
	printf("son %lu billetes de 50\n", cant_cincu);
	printf("son %lu billetes de 20\n", cant_veint);
	printf("son %lu billetes de 10\n", cant_diez);
	printf("son %lu billetes de 5\n", cant_cinco);

}


int main(void)

{
unsigned long cash = 4345;

cantidad_billetes_minima(cash);

return 0;
}


