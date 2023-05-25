#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define RED_MASK 0xF800 // 1111 1000 0000 0000
#define RED_SHIFT 11
#define GREEN_MASK 0x7E0 // 0111 1110 0000
#define GREEN_SHIFT 5
#define BLUE_MASK 0x1F // 0001 1111

#define MIN_TAM 6
#define INCREMENTO 10

/*

El formato RGB de 16 bits codifica colores en dos bytes. En dicho formato se destinan 5 bits para el rojo, 6 para el verde y 5 para el azul:
MSB 15 0 LSB +----+----+----+----+----+----+----+----++----+----+----+----+----+-         ---+----+----+ | r4 | r3 | r2 | r1 | r0 | g5 | g4 | g3 || g2 | g1 | g0 | b4 | b3 | b2 | b1 | b0 | +----+----+----+----+----+----+----+----++----+----+----+----+----+----+----+----+
por lo que habrá 32 valores posibles de rojo y azul y 64 de verde. Se pide:
a. Definir un tipo color_t y un tipo componente_t que permitan almacenar un color o una de sus componentes respectivamente.
b. Implementar una función
color_t compontentes_a_color(componente_t rojo, componente_t verde, componente_t azul);
que devuelva un color dadas sus componentes de rojo, verde y azul.
c. Implementar una función
componente_t componente_verde(color_t color);
que dado un color devuelva su valor de verde.

*/
/*
typedef uint8_t componente_t; 
typedef uint16_t color_t;


color_t compontentes_a_color(componente_t rojo, componente_t verde, componente_t azul)
{
    return (rojo << RED_SHIFT) | (verde << GREEN_SHIFT) | (azul); 
}

componente_t componente_verde(color_t color)
{
    return (color & GREEN_MASK) >> GREEN_SHIFT; 
}


int main(void)
{
    componente_t rojo = 0x01, verde = 0x02, azul = 0x04;
    
    color_t registro=0xF24F; //1111 0010 0100 1111

    printf("0x%X   0x%X\n", compontentes_a_color(rojo, verde, azul), componente_verde(registro));

    return 0;

} */

/*

2. Implementar una función
char **clonar_cadenas(const char **ss);
que reciba en ss un arreglo dinámico de cadenas y devuelva una copia del mismo en memoria nueva. La
cantidad de cadenas está indicada con el centinela NULL en la última posición.
Por ejemplo {"Hola", "que", "tal", NULL} es un arreglo con 3 cadenas.

*/

/*
void destruir_vector(char **s);

char **clonar_cadenas(char **s) 
{
    size_t i=0;
    char ** nuevo_vector;

    while(s[i]!=NULL)
    {
        i++;
    }
    nuevo_vector = malloc(sizeof(char *) * (i+1));
    if(nuevo_vector==NULL)
        return NULL;

    nuevo_vector[i+1]=NULL;

    for(size_t j=0; j<i; j++)
    {

        nuevo_vector[j] = malloc(sizeof(char) * (strlen(s[j]) + 1));
        if(nuevo_vector[j]==NULL)
        {
               fprintf(stderr, "aca\n");
            destruir_vector(nuevo_vector);
        }

        strcpy(nuevo_vector[j], s[j]);
    }
    return nuevo_vector;
}

void destruir_vector(char **s)
{
 
    for(size_t i; s[i]!= NULL; i++)
    {
        free(s[i]);
    }

    free(s);
}

int main(void)
{
    char *cadena[4];
    cadena[0] = "hola";
    cadena[1] = "como";
    cadena[2] = "estas";
    cadena[3] = NULL;
    char **nueva;

    nueva = clonar_cadenas(cadena);
   
   for(size_t i; i<3; i++)
    printf("%s\n", nueva[i]);
   
   destruir_vector(nueva);

    return 0;
}

*/

/*
Implementar una función
float *leer_flotantes(size_t *n);
que lea flotantes de stdin de a uno por línea hasta que se cierre la entrada. Se deben devolver los valores
leídos por el nombre y la cantidad de valores a través de n.
*/


float *leer_flotantes(size_t *n)
{
	float c;
    char buffer[MIN_TAM];
	float *temp ,*vec = NULL;
	
	size_t tengo = 0, pedidos = 0, i = 0;
	vec = malloc(MIN_TAM * sizeof(float));

	while(fgets(buffer, MIN_TAM, stdin))
	{
		if(tengo == pedidos)
		{
			temp = realloc(vec,(i * INCREMENTO + MIN_TAM)* sizeof(float));
			if(temp == NULL)
			{
				free(vec);
				return NULL;
			}
			vec = temp;
			pedidos = (i * INCREMENTO + MIN_TAM);
			i++;
		}
		vec[tengo++] = atof(buffer);
	}
    *n =pedidos;
	return vec; 
}

int main(void){
    size_t n;
    float *v = leer_flotantes(&n);
    if(v == NULL){
        return 1;
    }
    for(size_t i = 0; i < n; i++){
        printf("%f\n", v[i]);
    }
    
    free(v);
    return 0;
}
