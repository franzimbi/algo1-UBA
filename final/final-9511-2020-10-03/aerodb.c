#include "aerodb.h"

#define MAX_NOMBRE 63

typedef struct aeropuerto {
    char designacion[4];
    char nombre[MAX_NOMBRE];
    char ciudad[MAX_NOMBRE];
    char pais[MAX_NOMBRE];
    double lon;
    double lat;
} aeropuerto_t;

struct aerodb{
    aeropuerto_t *base_datos;
    size_t cant;
};


aerodb_t *aerodb_crear()
{
    aerodb_t * nuevo = malloc(sizeof(aerodb_t));
    if(nuevo==NULL)
        return NULL;
    
    nuevo->base_datos = NULL;
    nuevo->cant = 0;

    return nuevo;
}


bool aerodb_agregar(aerodb_t *a, const char *designacion, const char *nombre, const char *ciudad, const char *pais, double lat, double lon)
{
   aeropuerto_t*aux = realloc(a->base_datos, sizeof(aeropuerto_t)*(a->cant +1));
   if(aux==NULL)
        return false;
    
    a->base_datos = aux;

    strcpy(a->base_datos[a->cant].designacion, designacion);
    strcpy(a->base_datos[a->cant].nombre, nombre);
    strcpy(a->base_datos[a->cant].ciudad, ciudad);
    strcpy(a->base_datos[a->cant].pais, pais);

    a->base_datos[a->cant].lat = lat;
    a->base_datos[a->cant].lon = lon;

    a->cant+=1;
    return true;
}

size_t aerodb_cantidad(const aerodb_t *a)
{
    return a->cant;
}

const char *aerodb_nombre(const aerodb_t *a, const char *designacion)
{
    for(size_t i=0; i<(a->cant); i++)
    {
        if(!strcmp(a->base_datos[i].designacion, designacion))
            return a->base_datos[i].nombre;
    }

    return NULL;
}

const char *aerodb_ciudad(const aerodb_t *a, const char *designacion)
{
        for(size_t i=0; i<(a->cant); i++)
    {
        if(!strcmp(a->base_datos[i].designacion, designacion))
            return a->base_datos[i].ciudad;
    }

    return NULL;
}

const char *aerodb_pais(const aerodb_t *a, const char *designacion)
{
    for(size_t i=0; i<(a->cant); i++)
    {
        if(!strcmp(a->base_datos[i].designacion, designacion))
            return a->base_datos[i].pais;
    }

    return NULL;
}

double aerodb_lat(const aerodb_t *a, const char *designacion)
{
     for(size_t i=0; i<(a->cant); i++)
    {
        if(!strcmp(a->base_datos[i].designacion, designacion))
            return a->base_datos[i].lat;
    }

    return 0;
}

double aerodb_lon(const aerodb_t *a, const char *designacion)
{
        for(size_t i=0; i<(a->cant); i++)
    {
        if(!strcmp(a->base_datos[i].designacion, designacion))
            return a->base_datos[i].lon;
    }

    return 0;
}

void aerodb_destruir(aerodb_t *a)
{
    free(a);
}

bool aerodb_escribir(const aerodb_t *a, const char *ruta)
{
    FILE* fo=fopen(ruta, "wb");
    if(fo==NULL)
        return false;

    fwrite(&a->cant,sizeof(size_t), 1, fo);
    for(size_t i=0; i<a->cant; i++)
    {
        fwrite(a->base_datos[i].designacion,sizeof(char), 4, fo);
        fwrite(a->base_datos[i].nombre,sizeof(char), MAX_NOMBRE, fo);
        fwrite(a->base_datos[i].ciudad,sizeof(char), MAX_NOMBRE, fo);
        fwrite(a->base_datos[i].pais,sizeof(char), MAX_NOMBRE, fo);
        fwrite(&a->base_datos[i].lon, sizeof(double), 1, fo);
        fwrite(&a->base_datos[i].lat, sizeof(double), 1,fo);
    }

    fclose(fo);
    return true;
}

aerodb_t *aerodb_leer(const char *ruta)
{
    char designacion[4];
    char nombre[MAX_NOMBRE];
    char ciudad[MAX_NOMBRE];
    char pais[MAX_NOMBRE];
    double lon;
    double lat;

    size_t cant;

    aerodb_t* b = aerodb_crear();
    if(b==NULL)
        return NULL;

    FILE* fi=fopen(ruta, "rb");
    if(fi==NULL)
    {
        free(b);
        return NULL;
    }

    fread(&cant, sizeof(size_t),1,fi);

    for(size_t i=0; i<cant; i++)
    {

        fread(designacion, sizeof(char), 4, fi);
        fread(nombre, sizeof(char), MAX_NOMBRE, fi);
        fread(ciudad, sizeof(char), MAX_NOMBRE, fi);
        fread(pais, sizeof(char), MAX_NOMBRE, fi);
        fread(&lon, sizeof(double), 1, fi);
        fread(&lat, sizeof(double), 1, fi);

        aerodb_agregar(b, designacion, nombre, ciudad, pais, lat, lon);
    }

    fclose(fi);
    return b;
}

bool aerodb_buscar(aerodb_t *a, const char *designacion, char **nombre, char **ciudad, char **pais, double *lat, double *lon)
{
    size_t izq=0, der=(a->cant)-1, medio, c;

    while(izq<=der)
    {
        medio = (izq+der)/2;
        if( (c = strcmp(a->base_datos[medio].designacion, designacion))==0)
        {
           
            return true;
        }
        if(medio > c)
            der = medio-1;
        
        else
            izq=medio+1;
    }

    return false;
}
