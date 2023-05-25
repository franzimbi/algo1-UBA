#include"endiannes.h"


void escribir_int16_little_endian(FILE *f, int16_t v){

    uint8_t a[2];
    a[0]=(v & 0x00FF);
    a[1]=v >> 8;


    fwrite(a, sizeof(uint8_t), 2, f);
}




void escribir_int32_little_endian(FILE *f, int32_t v){
    uint8_t a[4];
    a[0] = v &  0x000000FF;
    a[1] = (v & 0x0000FF00) >> 8;
    a[2] = (v & 0x00FF0000) >> 16;
    a[3] = (v & 0xFF000000) >> 24;

    fwrite(a, sizeof(uint8_t), 4, f);

}

uint16_t leer_int16_little_endian(FILE *f){

    uint8_t a[2];
    fread(a, sizeof(uint8_t), 2, f);
    uint16_t y= a[0] << 8 | a[1];
    return y;

}




uint32_t leer_int32_little_endian(FILE *f){
    uint8_t a[4];
    fread(a, sizeof(uint8_t), 4, f);
    uint32_t y= a[0] << 24 | a[1] << 16 | a[2] << 8 | a[3];
    return y;

}


