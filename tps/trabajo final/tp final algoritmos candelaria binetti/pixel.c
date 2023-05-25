#include"pixel.h"


const struct colores_tabla tabla_color[] = {
    {"black", 0x0},

    {"white", 0xffffff},

    {"red", 0xff0000},

    {"lime", 0xff00},

    {"blue", 0xff},

    {"yellow", 0xffff00},

    {"cyan", 0x00ffff},

    {"magenta", 0xff00ff},

    {"silver", 0xc0c0c0},

    {"gray", 0x808080},

    {"maroon", 0x800000},

    {"olive",  0x808000},

    {"green", 0x8000},

    {"purple", 0x800080},

    {"teal", 0x8080},

    {"navy", 0x80}
};


pixel_t pixel_desde_rgb(componente_t rojo, componente_t verde, componente_t azul){
     return ((uint32_t)rojo << SHIFT_RED | (uint32_t)verde << SHIFT_GREEN | (uint32_t)azul);
}
componente_t pixel_get_rojo(pixel_t p){
    return (uint8_t)((p & MASK_RED) >> SHIFT_RED);
}

componente_t pixel_get_verde(pixel_t p){
    return(uint8_t)((p & MASK_GREEN) >> SHIFT_GREEN);
}

componente_t pixel_get_azul(pixel_t p){
    return (uint8_t)(p & MASK_BLUE);
}

void pixel_a_hsv(pixel_t p, short *h, float *s, float *v) {
    float rp = pixel_get_rojo(p) / 255.0;
    float vp = pixel_get_verde(p) / 255.0;
    float ap = pixel_get_azul(p) / 255.0;

    float cmax = rp > vp ? rp : vp;
    cmax = cmax > ap ? cmax : ap;

    float cmin = rp < vp ? rp : vp;
    cmin = cmin < ap ? cmin : ap;

    float delta = cmax - cmin;

    if(delta == 0)
        *h = 0;
    else if(cmax == rp)
        *h = (int)(60 * (vp - ap) / delta + 360.5) % 360;
    else if(cmax == vp)
        *h = (int)(60 * (ap - rp) / delta + 120.5) % 360;
    else
        *h = (int)(60 * (rp - vp) / delta + 240.5) % 360;

    *s = cmax == 0 ? 0 : (delta / cmax);
    *v = cmax;
}
pixel_t pixel_desde_hsv(short h, float s, float v) {
    float c = s * v;
    float x = c * (1 - fabs(fmodf(h / 60.0, 2) - 1));
    float m = v - c;

    float r = 0, v_ = 0, a = 0;

    if(h < 60)
        r = c, v_ = x;
    else if(h < 120)
        v_ = c, r = x;
    else if(h < 180)
        v_ = c, a = x;
    else if(h < 240)
        a = c, v_ = x;
    else if(h < 300)
        a = c, r = x;
    else
        r = c, a = x;

    return pixel_desde_rgb((r + m) * 255, (v_ + m) * 255, (a + m) * 255);
}






pixel_t pixel_desde_nombre(const char *nombre){
    for(size_t i = 0; i < sizeof(tabla_color) / sizeof(tabla_color[0]); i++)
        if(! strcmp(tabla_color[i].nombre, nombre))
            return tabla_color[i].pixel;
    return tabla_color[0].pixel;
}



