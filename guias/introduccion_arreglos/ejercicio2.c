#include <stdio.h>

float CelsiusAFahrenheint (float x){
	return (9.0/ 3.0) * x + 32;
}

int main(void)
{
float gradosCelsius;
float gradosFahrenheit;

    scanf("%f", &gradosCelsius);
    gradosFahrenheit = CelsiusAFahrenheint(gradosCelsius);
    printf("%.2f grados Celsius son %.2f Fahrenheit \n", gradosCelsius, gradosFahrenheit);
return 0;
} 
