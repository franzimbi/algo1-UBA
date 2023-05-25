// Zimbimbakis Francisco Manuel - 10 32 95


#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_ANCHO   1000
#define MAX_ALTO    1000
#define MAX_AUX 35

#define RED_MASK 0xFF0000// 1111 1111 0000 0000 0000 0000
#define GREEN_MASK 0xFF00 // 1111 1111 0000 0000
#define BLUE_MASK 0xFF // 1111 1111
#define RED_SHIFT 16
#define GREEN_SHIFT 8

typedef uint8_t componente_t;
typedef uint32_t pixel_t;
typedef pixel_t(*funcion_t)(pixel_t p, int parametro);

typedef enum {BLACK, WHITE, RED, LIME, BLUE, YELLOW, 
                   CYAN, MAGENTA, SILVER, GRAY, MAROON, OLIVE, 
                   GREEN, PURPLE, TEAL, NAVY}color_t;

typedef enum {INVERTIR=0, SATURAR=1, GAMA=2, BRILLO=3, CONTRASTE=4, MEZCLAR=5, SEPIA=6, MONOCROMO=7, TOASTER=8, VALENCIA=9} filtro_t;

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

pixel_t pixel_desde_rgb(componente_t rojo, componente_t verde, componente_t azul);
componente_t pixel_get_rojo(pixel_t p);
componente_t pixel_get_verde(pixel_t p);
componente_t pixel_get_azul(pixel_t p);
pixel_t pixel_desde_nombre(const char *nombre);
bool cadena_a_filtro(const char *nombre, filtro_t *filtro);
int numero_de_parametros(filtro_t filtro);
void aplicar_filtro(pixel_t imagen[MAX_ALTO][MAX_ANCHO], size_t ancho, size_t alto, filtro_t filtro, int parametro);
int leer_entero();
void pixel_a_hsv(pixel_t p, short *h, float *s, float *v);
pixel_t pixel_desde_hsv(short h, float s, float v);
pixel_t filtro_invertir(pixel_t p, int _);
pixel_t filtro_saturar(pixel_t p, int porcentaje);
pixel_t filtro_cambiar_gama(pixel_t p, int desplazamiento);
pixel_t filtro_cambiar_brillo(pixel_t p, int porcentaje);
pixel_t filtro_cambiar_contraste(pixel_t p, int porcentaje);
pixel_t filtro_mezclar(pixel_t p, int color);
pixel_t filtro_sepia(pixel_t p, int _);
pixel_t filtro_monocromo(pixel_t p, int porcentaje_umbral);
pixel_t filtro_toaster(pixel_t p, int _);
pixel_t filtro_valencia(pixel_t p, int _);
bool leer_imagen(pixel_t imagen[MAX_ALTO][MAX_ANCHO], size_t *ancho, size_t *alto);
void imprimir_imagen(pixel_t imagen[MAX_ALTO][MAX_ANCHO], size_t ancho, size_t alto);



//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const pixel_t valores_color[] = {[BLACK]=0x0, [WHITE]=0xFFFFFF, 
                                [RED]=0xFF0000, [LIME]=0xFF00, [BLUE]=0xFF,[YELLOW]=0xFFFF00, [CYAN]=0xFFFF, [MAGENTA]=0xFF00FF, [SILVER]=0xC0C0C0, [GRAY]=0x808080, [MAROON]=0x800000, [OLIVE]=0x808000, [GREEN]=0x8000, [PURPLE]=0x800080, [TEAL]=0x8080, [NAVY]=0x80};

const char nombres_color [][10] = {[BLACK]="black", [WHITE]="white", 
                                [RED]="red",[LIME]="lime",[BLUE]="blue", [YELLOW]="yellow", [CYAN]="cyan", [MAGENTA]="magenta", [SILVER]="silver", [GRAY]="gray", [MAROON]="maroon", [OLIVE]="olive", [GREEN]="green", [PURPLE]="purple", [TEAL]="teal", [NAVY]="navy"};

const char nombres_filtro[][10] = {[INVERTIR]="invertir", [SATURAR]="saturar",
                                [GAMA]="gama", [BRILLO]="brillo", [CONTRASTE]="contraste", [MEZCLAR]="mezclar", [SEPIA]="sepia", [MONOCROMO]="monocromo", [TOASTER]="toaster", [VALENCIA]="valencia"};

const int parametros_filtro[] = {[INVERTIR]=0, [SATURAR]=1,
                                [GAMA]=1, [BRILLO]=1, [CONTRASTE]=1, [MEZCLAR]=1, [SEPIA]=0, [MONOCROMO]=1, [TOASTER]=0, [VALENCIA]=0};

const funcion_t funciones[] = {[INVERTIR]=filtro_invertir,
                             [SATURAR]=filtro_saturar,[GAMA]=filtro_cambiar_gama, [BRILLO]=filtro_cambiar_brillo, [CONTRASTE]=filtro_cambiar_contraste, [MEZCLAR]=filtro_mezclar, [SEPIA]=filtro_sepia, [MONOCROMO]=filtro_monocromo, [TOASTER]=filtro_toaster, [VALENCIA]=filtro_valencia};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int main(int argc, char *argv[]) {
    if(argc < 2) {
        fprintf(stderr, "Hay que ingresar el nombre de un filtro\n");
        return 1;
    }

    filtro_t filtro;

    if(! cadena_a_filtro(argv[1], &filtro)) {
        fprintf(stderr, "El filtro %s no es un filtro valido\n", argv[1]);
        return 1;
    }
    int parametro = 0;
    int n_params = numero_de_parametros(filtro);
    if(n_params == 1) {
        if(argc < 3) {
            fprintf(stderr, "El filtro %s lleva un parametro\n", argv[1]);
            return 1;
        }

        if(filtro == mezclar) {
            parametro = pixel_desde_nombre(argv[2]);
        }
        else {
            parametro = atoi(argv[2]);
        }
    }

    pixel_t imagen[MAX_ALTO][MAX_ANCHO];
    size_t ancho, alto;

    if(! leer_imagen(imagen, &ancho, &alto)) {
        fprintf(stderr, "Hubo un error leyendo la imagen!\n");
        return 1;
    }

    aplicar_filtro(imagen, ancho, alto, filtro, parametro);

    imprimir_imagen(imagen, ancho, alto);

    return 0;
}


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

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

pixel_t pixel_desde_nombre(const char *nombre)
{
    size_t i;

    for(i=0; i < (sizeof(valores_color)/sizeof(valores_color[0])); i++)
    {
        if(strcmp(nombre, nombres_color[i]))
        {
            return valores_color[i];
        }
    }
    return valores_color[BLACK];
}

bool cadena_a_filtro(const char *nombre, filtro_t *filtro)
{
    filtro_t i;

    for(i=0; i< (sizeof(nombres_filtro)/sizeof(nombres_filtro[0])); i++)
    {
        if(!strcmp(nombre, nombres_filtro[i]))
        {
            *filtro = i;
            return true;
        }
    }
    return false;
}

int numero_de_parametros(filtro_t filtro)
{
    return parametros_filtro[filtro];
}

void aplicar_filtro(pixel_t imagen[MAX_ALTO][MAX_ANCHO], size_t ancho,
                     size_t alto, filtro_t filtro, int parametro)
{

funcion_t func_filtro = funciones[filtro];
    for(size_t i=0; i<alto; i++)
    {
        for(size_t j=0; j<ancho; j++)
        {
            imagen[i][j] = func_filtro(imagen[i][j], parametro);
        }
    }
}

int leer_entero()
{
	char x[MAX_AUX] = {0}, c;
	int i=0;
	
	c = getchar();
	if(c=='#')
	{
		while( getchar()!='\n');
		c = getchar();
	}
	if( (isspace(c))!=0 )
	{
		while( (isspace( c = getchar() ) )  !=  0 );
	}
	while( (isspace(c)) == 0 )
	{
		if(c==EOF)
			return -1;

		x[i] = c;
		i++;
		c=getchar();
	}
	return atoi(x);
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


bool leer_imagen(pixel_t imagen[MAX_ALTO][MAX_ANCHO], size_t *ancho, size_t *alto) {
    char aux[10];
    fgets(aux, 10, stdin);
    if(strcmp(aux, "P3\n"))
        return false;

    *ancho = leer_entero();
    *alto = leer_entero();
    int max = leer_entero();

    if(max != 255)
        return false;

    if(*ancho > MAX_ANCHO || *alto > MAX_ALTO)
        return false;

    for(int y = 0; y < *alto; y++)
        for(int x = 0; x < *ancho; x++) {
            componente_t rojo = leer_entero();
            componente_t verde = leer_entero();
            componente_t azul = leer_entero();
            imagen[y][x] = pixel_desde_rgb(rojo, verde, azul);
        }

    return true;
}

void imprimir_imagen(pixel_t imagen[MAX_ALTO][MAX_ANCHO], size_t ancho, size_t alto) {
    printf("P3\n");
    printf("%zd %zd 255\n", ancho, alto);

    for(int y = 0; y < alto; y++)
        for(int x = 0; x < ancho; x++) {
            pixel_t pixel = imagen[y][x];
            printf("%d %d %d\n", pixel_get_rojo(pixel), pixel_get_verde(pixel), pixel_get_azul(pixel));
        }
}
