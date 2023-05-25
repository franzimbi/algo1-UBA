/*
Un microcontrolador posee el siguiente registro para el manejo de datos a través de un puerto serie que puede conectarse a una PC:

| bit 7 |   6   |   5   |   4   |   3   |   2   |   1   | bit 0 |
+-------+-------+-------+-------+-------+-------+-------+-------+
| RXCIE | TXCIE | UDRIE |  RXEN |  TXEN |  CHR9 |  RXB8 |  TXB8 |
+-------+-------+-------+-------+-------+-------+-------+-------+

a) Escriba el código de una función denominada transmision_completa() que indique, a partir del contenido del byte de control (bit TXCIE), y mediante la devolución de un valor por el nombre, si se ha completado o no, la transmisión de un símbolo por el puerto serie.

c) Modifique el código de la función pedida en el punto a) para que la misma indique, mediante la devolución de un valor por la interfaz, si se ha completado o no la transmisión. Dar un ejemplo de invocación de esta función. Debe utilizarse máscaras y operadores de bits para leer cada bit del registro de datos.
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define MASK_RXCIE 0x80 //1000 0000
#define MASK_TXCIE 0x40 //0100 0000
#define SHIFT_TXCIE 6

bool transmision_completa(uint8_t registro)
{
    return (registro & MASK_TXCIE) != 0;
}

int main(void)
{
    uint8_t registro = 0x1A; //0001 1010
    
    printf("%s\n", transmision_completa(registro) ? "TERMINO TRANSMISION" : "TRANSMISION NO TERMINADA");
    return EXIT_SUCCESS;
}
