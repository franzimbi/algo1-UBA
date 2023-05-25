#include <stdio.h>
#define pi 3.14

float diametro(float r){

	return 2*r;
}

float circunferencia(float r){
	return 2*pi*r;
}

float area(float r)
{
	return pi*r*r;
}

float volumen(float r, float h)
{
	return area(r)* h;
}

float areaCilindro(float r, float h)
{
	return area(r) * h;
}

int main(void)
{
	float r, h;

printf("ingrese radio y altura del cilindro\n");

scanf("%f", &r);
scanf("%f", &h);

printf("diametro del cilindro: %.2f\n circunferencia: %.2f\n area de la base: %.2f\n volumen del cilndro: %.2f\n area del cilindro: %.2f\n", diametro(r), circunferencia(r), area(r), volumen(r,h), areaCilindro(r,h));

return 0;
}
