#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#define MASK 0x1
// HACER: implementar la funcion
// NO se permite usar funciones de la biblioteca estandar



void hex_codificar(uint32_t n, char *s) {

    size_t i;

    for(i=0; i<3; i++)
    {
        uint8_t nro = n | (MASK << i);
        fprintf(stderr, "%i\n", nro);
        //s[i] = 
    }

    //s[i]='\0';

}

int main(void) {
    char s[10];
    hex_codificar(0x3f4, s);
    fprintf(stderr, "%s\n", s);
    assert(!strcmp(s, "3f4"));


    // OPCIONAL: Pruebas adicionales. Sugerencias:
    // - 0x0
    // - 0x1
    // - 0xffffffff
    // - 0x80000000

    printf("%s: OK\n", __FILE__);
    return 0;
}
