/*
Alumno: Zimbimbakis Francisco Manuel
padron: 10 32 95
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

typedef uint8_t pixel_t;

typedef struct {
    pixel_t **lienzo;
    size_t ancho, alto;
} imagen_t;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

void imagen_destruir(imagen_t *imagen);
imagen_t *_imagen_crear(size_t ancho, size_t alto);
imagen_t *imagen_leer_stdin();
int leer_entero();
void imagen_escribir(const imagen_t *imagen);
imagen_t *imagen_recortar(const imagen_t *imagen, size_t x0, size_t y0, size_t ancho, size_t alto);
imagen_t *imagen_clonar(const imagen_t *imagen);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

int main(void) {
    fprintf(stderr, "Leyendo imagen...");
    imagen_t *imagen_original = imagen_leer_stdin();
    if(imagen_original == NULL) {
        fprintf(stderr, "\nERROR: No se pudo leer imagen!\n");
        return 1;
    }
    fprintf(stderr, " OK!\n");

    fprintf(stderr, "Clonando imagen...");
    imagen_t *imagen_copia = imagen_clonar(imagen_original);
    if(imagen_copia == NULL) {
        imagen_destruir(imagen_original);
        fprintf(stderr, "\nERROR: No se pudo clonar imagen!\n");
        return 1;
    }
    fprintf(stderr, " OK!\n");

    fprintf(stderr, "Destruyendo imagen original...");
    imagen_destruir(imagen_original);
    fprintf(stderr, " OK!\n");

    fprintf(stderr, "Recortando imagen...");
    imagen_t *imagen_recortada = imagen_recortar(imagen_copia, 300, 100, 330, 300);
    if(imagen_recortada == NULL) {
        imagen_destruir(imagen_copia);
        fprintf(stderr, "\nERROR: No se pudo recortar la imagen.\n");
        return 1;
    }
    fprintf(stderr, " OK!\n");

    fprintf(stderr, "Destruyendo imagen de copia...");
    imagen_destruir(imagen_copia);
    fprintf(stderr, " OK!\n");

    fprintf(stderr, "Escribiendo imagen...");
    imagen_escribir(imagen_recortada);
    fprintf(stderr, " OK!\n");

    fprintf(stderr, "Recortando imagen para que falle...");
    if(imagen_recortar(imagen_recortada, 100, 300, 20, 20) != NULL) {
        imagen_destruir(imagen_recortada);
        fprintf(stderr, "Imagen de tamano cero no vale NULL\n");
        return 1;
    }
    fprintf(stderr, " OK!\n");

    fprintf(stderr, "Destruyendo imagen recortada...");
    imagen_destruir(imagen_recortada);
    fprintf(stderr, " OK!\n");

    fprintf(stderr, "Pasaron todos los tests!\nComprobá con Valgrind que no haya pérdidas de memoria\n");

    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

imagen_t *_imagen_crear(size_t ancho, size_t alto)
{
    imagen_t *imagen;


    imagen = malloc(sizeof(imagen_t));
    if(imagen==NULL)
        return NULL;

    imagen->ancho= ancho;
    imagen->alto=alto;
    imagen->lienzo = malloc(alto * sizeof(pixel_t*));
        if(imagen->lienzo==NULL)
        return NULL;

    for(size_t i=0; i<alto; i++)
    {
        imagen->lienzo[i] = malloc(ancho * sizeof(pixel_t));
            if(imagen->lienzo[i]==NULL)
            {
                imagen_destruir(imagen);
                return NULL;
            }
    }

    return imagen;
}

void imagen_destruir(imagen_t *imagen)
{
    for(size_t i=0; i<(imagen->alto); i++)
    {
        free(imagen->lienzo[i]);
    }
    free(imagen->lienzo);
    free(imagen);
}

int leer_entero()
{
	char x[3] = {0}, c;
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

imagen_t *imagen_leer_stdin()
{
    size_t ancho, alto;
    imagen_t *imagen;

    leer_entero(); //P2
    ancho = leer_entero();
    alto = leer_entero();
    leer_entero(); //MAXIMO DE PIXELES (255)

    imagen = _imagen_crear(ancho, alto);
        if(imagen==NULL)
            return NULL;

    for(size_t i=0; i<alto; i++)
    {
        for(size_t j=0; j<ancho; j++)
        {
            imagen->lienzo[i][j]=leer_entero();
        }
    }
    return imagen;
}

void imagen_escribir(const imagen_t *imagen)
{
    
    printf("P2\n%zu\t%zu\n255\n", imagen->ancho, imagen->alto);
     for(size_t i=0; i<(imagen->alto); i++)
    {
        for(size_t j=0; j<(imagen->ancho); j++)
        {
            printf("%hhu\n",imagen->lienzo[i][j]);
        }
    }
}

imagen_t *imagen_recortar(const imagen_t *imagen, size_t x0, size_t y0, size_t ancho, size_t alto)
{
    imagen_t *recorte;
    size_t ancho_recorte=ancho, alto_recorte=alto;

    if(ancho_recorte>((imagen->ancho)-x0))
        ancho_recorte = (imagen->ancho)-x0;
    
    if(alto_recorte>((imagen->alto)-y0))
        alto_recorte = (imagen->alto)-y0;
    
    recorte = _imagen_crear(ancho_recorte, alto_recorte);

        if(recorte==NULL)
        {
            return NULL;
        }
    for(size_t i=0; i<alto; i++)
    {
        if((y0+i)>=(imagen->alto))
            break;
        for(size_t j=0; j<ancho; j++)
        {
            if((x0+j)>=(imagen->ancho))
                break;
            recorte->lienzo[i][j] = imagen->lienzo[y0+i][x0+j];
        }
    }

    if((x0>ancho || y0>alto))
    {
        imagen_destruir(recorte);
        return NULL;
    }

    return recorte;
}

imagen_t *imagen_clonar(const imagen_t *imagen)
{
    return imagen_recortar(imagen, 0, 0, imagen->ancho, imagen->alto); 
}
