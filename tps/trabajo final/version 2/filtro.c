#include "filtro.h"


typedef pixel_t(*funcion_t)(pixel_t p, int parametro);

struct color_tabla{
    char *nombre;
    pixel_t valor;
};

struct filtro_tabla{
    char *nombre;
    int parametro;
    funcion_t funcion;
};

struct imagen{
    pixel_t **lienzo;
    size_t ancho, alto;
};

const colores_tabla tabla_color[] = {
    [BLACK]={"black", 0x0},
    [WHITE]={"white", 0xffffff},
    [RED]={"red", 0xff0000},
    [LIME]={"lime", 0xff00},
    [BLUE]={"blue", 0xff},
    [YELLOW]={"yellow", 0xffff00},
    [CYAN]={"cyan", 0x00ffff},
    [MAGENTA]={"magenta", 0xff00ff},
    [SILVER]={"silver", 0xc0c0c0},
    [GRAY]={"gray", 0x808080},
    [MAROON]={"maroon", 0x800000},
    [OLIVE]={"olive",  0x808000},
    [GREEN]={"green", 0x8000},
    [PURPLE]={"purple", 0x800080},
    [TEAL]={"teal", 0x8080},
    [NAVY]={"navy", 0x80}
};

const filtros_tabla tabla_filtro[] = {
    [INVERTIR]={"invertir", 0, filtro_invertir},
    [SATURAR]={"saturar", 1, filtro_saturar},
    [GAMA]={"gama", 1, filtro_cambiar_gama},
    [BRILLO]={"brillo", 1, filtro_cambiar_brillo},
    [CONTRASTE]={"contraste", 1, filtro_cambiar_contraste},
    [MEZCLAR]={"mezclar", 1, filtro_mezclar},
    [SEPIA]={"sepia", 0, filtro_sepia},
    [MONOCROMO]={"monocromo", 1, filtro_monocromo},
    [TOASTER]={"toaster", 0, filtro_toaster},
    [VALENCIA]={"valencia", 0, filtro_valencia},
};

bool cadena_a_filtro(const char *nombre, filtro_t *filtro)
{
    filtro_t i;

    for(i=0; i< (sizeof(tabla_filtro)/sizeof(tabla_filtro[0])); i++)
    {
        if(!strcmp(nombre, tabla_filtro[i].nombre))
        {
            *filtro = i;
            return true;
        }
    }
    return false;
}

int numero_de_parametros(filtro_t filtro)
{
    return tabla_filtro[filtro].parametro;
}

void aplicar_filtro(imagen_t* imagen, filtro_t filtro, int parametro)
{

funcion_t func_filtro = tabla_filtro[filtro].funcion;
    for(size_t i=0; i<imagen->alto; i++)
    {
        for(size_t j=0; j<imagen->ancho; j++)
        {
            imagen->lienzo[i][j] = func_filtro(imagen->lienzo[i][j], parametro);
        }
    }
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

pixel_t filtro_invertir(pixel_t p, int _) {
    return pixel_desde_rgb(255 - pixel_get_rojo(p), 255 - pixel_get_verde(p), 255 - pixel_get_azul(p));
}

pixel_t filtro_saturar(pixel_t p, int porcentaje) {
    short h;
    float s, v;
    pixel_a_hsv(p, &h, &s, &v);

    s *= (1 + porcentaje / 100.0);

    if(s < 0)
        s = 0;
    else if(s > 1)
        s = 1;

    return pixel_desde_hsv(h, s, v);
}

pixel_t filtro_cambiar_gama(pixel_t p, int desplazamiento) {
    short h;
    float s, v;
    pixel_a_hsv(p, &h, &s, &v);

    h = (h + desplazamiento) % 360;

    return pixel_desde_hsv(h, s, v);
}

pixel_t filtro_cambiar_brillo(pixel_t p, int porcentaje) {
    short h;
    float s, v;
    pixel_a_hsv(p, &h, &s, &v);

    v += porcentaje / 100.;

    if(v < 0)
        v = 0;
    else if(v > 1)
        v = 1;

    return pixel_desde_hsv(h, s, v);
}

pixel_t filtro_cambiar_contraste(pixel_t p, int porcentaje) {
    short h;
    float s, v;
    pixel_a_hsv(p, &h, &s, &v);

    v *= 1 + porcentaje / 100.;

    if(v < 0)
        v = 0;
    else if(v > 1)
        v = 1;

    return pixel_desde_hsv(h, s, v);
}

pixel_t filtro_mezclar(pixel_t p, int color) {
    pixel_t c = color;

    return pixel_desde_rgb(
        (pixel_get_rojo(p) + pixel_get_rojo(c)) / 2,
        (pixel_get_verde(p) + pixel_get_verde(c)) / 2,
        (pixel_get_azul(p) + pixel_get_azul(c)) / 2);
}

pixel_t filtro_sepia(pixel_t p, int _) {
    componente_t r = pixel_get_rojo(p);
    componente_t v = pixel_get_verde(p);
    componente_t a = pixel_get_azul(p);

    int rn = r * 0.393 + v * 0.769 + a * 0.189;
    int vn = r * 0.349 + v * 0.686 + a * 0.168;
    int an = r * 0.272 + v * 0.534 + a * 0.131;

    if(rn > 255) rn = 255;
    if(vn > 255) vn = 255;
    if(an > 255) an = 255;

    return pixel_desde_rgb(rn, vn, an);
}

pixel_t filtro_monocromo(pixel_t p, int porcentaje_umbral) {
    short h;
    float s, v;
    pixel_a_hsv(p, &h, &s, &v);

    return (v > porcentaje_umbral / 100.) ? pixel_desde_rgb(255, 255, 255) : pixel_desde_rgb(0, 0, 0);
}

pixel_t filtro_toaster(pixel_t p, int _) {
    p = filtro_mezclar(p, pixel_desde_rgb(51, 0, 0));

    short h;
    float s, v;
    pixel_a_hsv(p, &h, &s, &v);

    v = v * 1.5 + 0.2;
    s *= 0.8;
    h = (h + 20) % 360;

    if(v > 1)
        v = 1;

    return pixel_desde_hsv(h, s, v);
}

pixel_t filtro_valencia(pixel_t p, int _) {
    float r = pixel_get_rojo(p) / 100.;
    float ve = pixel_get_verde(p) / 100.;
    float a = pixel_get_azul(p) / 100.;

    r = 0.23 + r - 2 * 0.23 * r;
    ve = 0.01 + ve - 2 * 0.01 * ve;
    a = 0.22 + a - 2 * 0.22 * a;

    if(r > 1) r = 1;
    if(ve > 1) ve = 1;
    if(a > 1) a = 1;

    if(r < 0) r = 0;
    if(ve < 0) ve = 0;
    if(a < 0) a = 0;

    p = filtro_mezclar(p, pixel_desde_rgb(r * 255, ve * 255, a * 255));

    short h;
    float s, v;
    pixel_a_hsv(p, &h, &s, &v);

    v = v * 1.08 - 0.08;
    if(v > 1)
        v = 1;
    if(v < 0)
        v = 0;

    p = pixel_desde_hsv(h, s, v);
    pixel_t c = filtro_sepia(p, 0);

    return pixel_desde_rgb(
        pixel_get_rojo(p) * 0.92 + pixel_get_rojo(c) * 0.08,
        pixel_get_verde(p) * 0.92 + pixel_get_verde(c) * 0.08,
        pixel_get_azul(p) * 0.92 + pixel_get_azul(c) * 0.08);
}

pixel_t pixel_desde_nombre(const char *nombre)
{
    size_t i;

    for(i=0; i < (sizeof(tabla_color)/sizeof(tabla_color[0])); i++)
    {
        if(!strcmp(nombre, tabla_color[i].nombre))
        {
            return tabla_color[i].valor;
        }
    }
    return tabla_color[BLACK].valor;
}