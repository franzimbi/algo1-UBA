#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define RED_MASK 0x00FF0000
#define GREEN_MASK 0x0000FF00
#define BLUE_MASK 0x000000FF
#define RED_SHIFT 16
#define GREEN_SHIFT 8

typedef uint8_t componente_t;
typedef uint32_t pixel_t;


typedef enum {black, white, red, lime, blue, yellow, 
                   cyan, magenta, silver, gray, maroon, olive, 
                   green, purple, teal, navy}color_t;

const pixel_t valores_color[] = {[black]=0x0, [white]=0xFFFFFF, 
                                [red]=0xFF0000, [lime]=0xFF00, [blue]=0xFF,[yellow]=0xFFFF00, [cyan]=0xFFFF, [magenta]=0xFF00FF, [silver]=0xC0C0C0, [gray]=0x808080, [maroon]=0x800000, [olive]=0x808000, [green]=0x8000, [purple]=0x800080, [teal]=0x8080, [navy]=0x80};

const char nombres_color [][10] = {[black]="black", [white]="white", 
                                [red]="red",[lime]="lime",[blue]="blue", [yellow]="yellow", [cyan]="cyan", [magenta]="magenta", [silver]="silver", [gray]="gray", [maroon]="maroon", [olive]="olive", [green]="green", [purple]="purple", [teal]="teal", [navy]="navy"};

pixel_t pixel_desde_rgb(componente_t rojo, componente_t verde, componente_t azul)
{
    return (rojo << RED_SHIFT) | (verde << GREEN_SHIFT) | azul;
}

componente_t pixel_get_rojo(pixel_t p)
{
    return (p & RED_MASK) >> RED_SHIFT;
}

componente_t pixel_get_verde(pixel_t p)
{
    return (p & GREEN_MASK) >> GREEN_SHIFT;
}

componente_t pixel_get_azul(pixel_t p)
{
    return p & BLUE_MASK;
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
