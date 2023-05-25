#include <stdio.h>

float cuad(float x){

	return x*x;
}

float squart(float n){

float i=0, res=0;

do{
	i = i+0.01;
	res = i*i;

}while(res<=n);

return i;
}


int main(void){

float x,y,z;
float norma;

printf("introduce (x,y,z) entre enters\n");

scanf("%f", &x);
scanf("%f", &y);
scanf("%f", &z);

x = cuad(x) + cuad(y) + cuad(z);
norma= squart(x);

printf("la norma es: %f \n", norma);

return 0;
}
