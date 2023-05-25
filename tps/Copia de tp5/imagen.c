#include "imagen.h"

 struct imagen{
    pixel_t **lienzo;
    size_t ancho, alto;
};


static imagen_t *_imagen_crear(size_t ancho, size_t alto)
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

static int leer_entero(FILE * f)
{
	char x[3] = {0}, c;
	int i=0;
	
	c = fgetc(f);
	if(c=='#')
	{
		while( fgetc(f)!='\n');
		c = fgetc(f);
	}
	if( (isspace(c))!=0 )
	{
		while( (isspace( c = fgetc(f) ) )  !=  0 );
	}
	while( (isspace(c)) == 0 )
	{
		if(c==EOF)
			return -1;

		x[i] = c;
		i++;
		c=fgetc(f);
	}
	return atoi(x);
}

imagen_t *imagen_leer_ppm(FILE * f)
{
    size_t ancho, alto;
    imagen_t *imagen;

    leer_entero(f); //P2
    ancho = leer_entero(f);
    alto = leer_entero(f);
    leer_entero(f); //MAXIMO DE PIXELES (255)

    imagen = _imagen_crear(ancho, alto);
        if(imagen==NULL)
            return NULL;

    componente_t rgb[3];
    for(size_t i=0; i<alto; i++)
    {
        for(size_t j=0; j<ancho; j++)
        {
            rgb[0] = leer_entero(f);
            rgb[1] = leer_entero(f);
            rgb[2] = leer_entero(f);

            imagen->lienzo[i][j] = pixel_desde_rgb(rgb[0], rgb[1], rgb[2]);
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

void imagen_escribir_ppm(const imagen_t *imagen, FILE *f)
{
    
    fprintf(f, "P3\n%zu\t%zu\n255\n", imagen->ancho, imagen->alto);
     for(size_t i=0; i<(imagen->alto); i++)
    {
        for(size_t j=0; j<(imagen->ancho); j++)
        {
            componente_t rgb[3];

            rgb[0]=pixel_get_rojo(imagen->lienzo[i][j]);
            rgb[1]=pixel_get_verde(imagen->lienzo[i][j]);
            rgb[2]=pixel_get_azul(imagen->lienzo[i][j]);


            fprintf(f, "%i %i %i\n",rgb[0], rgb[1], rgb[2]);
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

void espejar_horizontalmente(imagen_t * imagen)
{
	size_t temp;

	for(size_t i=0; i<imagen->alto; i++)
	{
		for(size_t j=0; j<=imagen->ancho/2 ; j++)
		{
			temp = imagen->lienzo[i][j];
			imagen->lienzo[i][j] = imagen->lienzo[i][(imagen->ancho)-j-1];
			imagen->lienzo[i][(imagen->ancho)-j-1] = temp;
		}	
	}
}

void espejar_verticalmente(imagen_t * imagen)
{
	size_t temp;

	for(size_t i=0; i<imagen->alto/2; i++)
	{
		for(size_t j=0; j<=imagen->ancho; j++)
		{
			temp = imagen->lienzo[i][j];
			imagen->lienzo[i][j] = imagen->lienzo[(imagen->alto)-i-1][j];
			imagen->lienzo[(imagen->alto)-i-1][j] = temp;
		}	
	}
}

static int32_t calcular_tamano_bmp(const imagen_t *imagen)
{   
    size_t i;
    for(i=0; (imagen->ancho * 3 + i)%4 != 0; i++);

    return (54 + (imagen->alto * ( (imagen->ancho) * 3 + i ))); 
}

static void escribir_encabezado_BMP(const imagen_t *imagen, FILE *f)
{
        //encabezado de archivo
    char tipo[2] = "BM";
    int16_t reservado[2] = {0};
    int32_t offset = 54;
    int32_t tamano_encabezado_archivo = calcular_tamano_bmp(imagen);

    //encabezado de imagen
    int32_t tamano_encabezado_imagen = 40;

    int16_t planos = 1, bits_de_color = 24;
    int32_t compresion = 0, tamano_de_imagen = 0, resolucion_y = 0,
            resolucion_x = 0, tablas_de_color = 0, colores_importantes = 0; 



    //escritura encabezado del archivo
    fwrite(tipo, sizeof(char), 2, f);
    escribir_int32_little_endian(f, tamano_encabezado_archivo);
    fwrite(reservado, sizeof(int16_t), 2, f);
    escribir_int32_little_endian(f, offset);
    //escritura encabezado de la imagen
    escribir_int32_little_endian(f, tamano_encabezado_imagen);
    escribir_int32_little_endian(f, imagen->ancho);
    escribir_int32_little_endian(f, imagen->alto);
    escribir_int16_little_endian(f, planos);
    escribir_int16_little_endian(f, bits_de_color);
    escribir_int32_little_endian(f, compresion);
    escribir_int32_little_endian(f, tamano_de_imagen);
    escribir_int32_little_endian(f, resolucion_x);
    escribir_int32_little_endian(f, resolucion_y);
    escribir_int32_little_endian(f, tablas_de_color);
    escribir_int32_little_endian(f, colores_importantes);
}

void imagen_escribir_BMP(const imagen_t *imagen, FILE *f)
{
    int8_t ceros = 0;
    escribir_encabezado_BMP(imagen, f);
    

    for(size_t i=0; i<(imagen->alto); i++)
    {
        for(size_t j=0; j<(imagen->ancho); j++)
        {
        componente_t b,g,r;

        b = pixel_get_azul(imagen->lienzo[(imagen->alto)-i-1][j]);
        g= pixel_get_verde(imagen->lienzo[(imagen->alto)-i-1][j]);
        r = pixel_get_rojo(imagen->lienzo[(imagen->alto)-i-1][j]);

        fwrite(&b, sizeof(componente_t), 1,f);
        fwrite(&g, sizeof(componente_t), 1,f);
        fwrite(&r, sizeof(componente_t), 1,f);

        }

        size_t linea = (imagen->ancho *3);
        while( linea%4 )
        {
            fwrite(&ceros, sizeof(int8_t),1,f);
            linea++;
        }
    
    }
}

imagen_t * imagen_leer_BMP(FILE* f)
{
    int32_t ancho=0, alto=0;
    imagen_t * imagen;
    char bm[2];
    int32_t trash = 0;

    fread(bm, sizeof(char), 2,f); //LE BM
    fread(&trash, sizeof(int32_t), 1,f); //LEO TAMANO_ENCABEZADO_ARCHIVO
    fread(&trash, sizeof(int16_t), 1, f); //LEO RESERVADO
    fread(&trash, sizeof(int16_t), 1, f); //LEO RESERVADO
    fread(&trash, sizeof(int32_t), 1, f); //LEO OFFSET
    fread(&trash, sizeof(int32_t), 1, f); //LEO TAMANO_ENCABEZADO_IMAGEN
    fread(&ancho, sizeof(int32_t), 1, f); //LEO Y GUARDO ANCHO
    fread(&alto, sizeof(int32_t), 1, f); //LEO Y GUARDO ALTO

    imagen = _imagen_crear(int32_a_big_endian(ancho), int32_a_big_endian(alto));
        if(imagen == NULL)
            return NULL;
    
    fread(&trash, sizeof(int16_t), 1,f); //LEE PLANOS
    fread(&trash, sizeof(int16_t), 1,f); //LEE BITS_DE_COLOR
    fread(&trash, sizeof(int32_t), 1, f); //LEE COMPRESION
    fread(&trash, sizeof(int32_t), 1, f); //LEE_TAMANO_IMAGEN
    fread(&trash, sizeof(int32_t), 1, f); //LEE RESOLUCION_X
    fread(&trash, sizeof(int32_t), 1, f); //LEE RESOLUCION_Y
    fread(&trash, sizeof(int32_t), 1, f); //LEE TABLAS_DE_COLOR
    fread(&trash, sizeof(int32_t), 1, f); // LEE COLORES_IMPORTANTES

    for(size_t i=0; i< imagen->alto; i++)
    {
        componente_t bgr[3];
        for(size_t j=0; j< imagen->ancho; j++)
        {
            fread(bgr,sizeof(componente_t), 3, f);

            imagen->lienzo[i][j] = pixel_desde_rgb(bgr[2], bgr[1], bgr[0]);
        }
    }
    return imagen;
}
