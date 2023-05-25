/*
Para un aplicativo a ejecutarse sobre una plataforma de 32 bits que contendrá una interfaz gráfica de usuario (GUI), se requiere disponer de funciones para el tratamiento de colores de los elementos gráficos de la interfaz. El color de cualquier elemento gráfico se almacenará en una variable de tipo int sin signo de 32 bits, de acuerdo a la convención RGB (ejemplo: un color con representación RGB = 0xFFCCAA se corresponde con 0xFF, 0xCC y 0xAA para las componentes Rojo, Verde y Azul, respectivamente). Se pide:

a) Escribir una función denominada Rojo() que reciba como argumento el color en representación RGB sobre una variable de tipo uint32_t, que devuelva por el nombre la componente de color rojo como un uint8_t. Dar un ejemplo de invocación de la función.

b)Idem a. para una función denominada Verde() que devuelva la componente verde. Dar un ejemplo de invocación de la función.

c)Idem a para una función denominada Azul() que devuelva la componente Azul. Dar un ejemplo de invocación de la función.

d) Escribir una función llamada componentesRGB() que reciba como argumentos el color en notación RGB sobre una variable de tipo uint32_t, y devuelva a través de la interfaz las 3 componentes R, G, y B simultáneamente sobre variables de tipo uint8_t. Dar un ejemplo de invocación de esta función.

e) Escribir los prototipos de las funciones desarrolladas en los cuatro puntos anteriores.

1111 1111  1100 1100  1010 1010
*/

#include <stdio.h>
#include <stdint.h>

#define REDMASK 0xFF0000
#define GREENMASK 0xFF00
#define BLUEMASK 0x00FF


uint8_t rojo(uint32_t color)
{
    return (color & REDMASK)>>16;
}

uint8_t verde(uint32_t color)
{
    return(color & GREENMASK)>>8;
}

uint8_t azul(uint32_t color)
{
    return color & BLUEMASK;
}

uint32_t empaquetar_color(uint8_t r, uint8_t g, uint8_t b)
{
    return (r<<16) | (g<<8) | b;
}

int main(void)
{
    uint32_t rgb = 0xFFCCAA;

    printf("0x%x el rojo es: 0x%x\n", rgb, rojo(rgb));
    printf("0x%x el azul es: 0x%x\n", rgb, azul(rgb));
    printf("0x%x el verde es: 0x%x\n", rgb, verde(rgb));
    printf("color: 0x%x\n", empaquetar_color(0x43, 0xf2, 0x55));


    return 0;
}
