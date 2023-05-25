#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/*

1. Un procesador usa para enviar datos un registro como el siguiente:

|WLO|WHI|---|D3 |D2 |D1 |D0 |---| 
 7    6   5   4   3   2   1   0

El bit WLO habilita el envío del nibble (medio byte) bajo, el bit WHI habilita el envío del nibble alto y los bits D3,D2,D1,D0 son el nibble a transmitir.
Para enviar un byte se debe:
i. Escribir la mitad baja del byte en D3,D2,D1,D0.
ii. Poner WLO en 1 (para hacer que se mande el nibble bajo).
iii. Escribir la mitad alta del byte en D3,D2,D1,D0.
iv. Poner WHI en 1 (para hacer que se mande el nibble alto).
Programar una función
void enviar_dato(uint8_t *registro, uint8_t dato);
que reciba el registro y un dato y envíe el dato según la secuencia descripta.
Nota: Si se tuviera que enviar el dato 0xAB el nibble alto estará representado por 0xA mientras que el bajo por 0xB.

*/
/*

#define WLO_MASK 0x80 // 1000 0000
#define WHI_MASK 0x40 //0100 0000
#define BYTES_MASK 0x1E// 0001 1110
#define ALTO_MASK 0xF0 //1111 0000
#define ALTO_SHIFT 4
#define BAJO_MASK 0xF //0000 1111
#define BAJO_SHIFT 4

void enviar_dato(uint8_t *registro, uint8_t dato) //dato: AAAA BBBB
{
    *registro = (*registro | WLO_MASK) & ((dato & (~ ALTO_MASK)) >> (ALTO_SHIFT - 1));

    *registro = (*registro | WHI_MASK) & ( (dato & (~BAJO_MASK)) << (BAJO_SHIFT - 1));
}
*/

/*

a. Implementar la función:
char **extraer_cadenas(const char *ss[], size_t sn, size_t indices[], size_t indicesn);
que reciba un arreglo de cadenas de caracteres ss de longitud sn y que devuelva un arreglo de cadena de caracteres de longitud indicesn que contenga únicamente las cadenas que correspondan a los indices indicados. Todo debe estar contenido en memoria nueva.
Ejemplo, si se llama a la función con ss = {"hola", "que", "tal", "estas"} (sn = 4) y con indices = {1, 3} (indicesn = 2) se debe devolver {"que", "estas"}.
b. Implementar la función:
void liberar_cadenas(char *ss[], size_t sn);
que reciba ss, un arreglo dinámico de cadenas de caracteres dinámicas de longitud sn y libere toda su
memoria asociada.

*/

char **extraer_cadenas(const char *ss[], size_t sn, size_t indices[], size_t indicesn)
{
    
}




int main(void)
{
  /*  uint8_t registro = 0xFF;
    uint8_t dato = 0xA2;

    enviar_dato(&registro, dato);

    printf("0x%X\n", registro); */

    return 0;
}