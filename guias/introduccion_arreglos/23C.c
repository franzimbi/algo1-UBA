
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef unsigned short short_u;

bool fecha_valida (short_u day, short_u month, short_u year)
{
	if(day<32 && month<13)
	{	
		if(month==2 && day<28)
			return true;
		if(month%2 != 0 && month<=7)
			return true;
		if(month%2 ==0 && month<=6 && day<31)
			return true;
		if(month%2 ==0 && month>=8 && month != 2)
			return true;
	}
	return false;
}

int main(void)
{
	short_u day, month, year, valid;

	scanf("%hd", &day);
	scanf("%hd", &month);
	scanf("%hd", &year);

	valid= fecha_valida(day,month,year);

	if(valid !=0)
	{
		printf("fecha valida\n");
	}else {
		printf("fecha invalida\n");
	}

return 0;

}
