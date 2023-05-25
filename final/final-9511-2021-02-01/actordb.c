#include "actordb.h"

// Escribir codigo aqui

struct actor{
    char nombre[NOMBRE_MAX];
    fecha_t nacimiento;
};

actor_t *actor_crear(const char *nombre, fecha_t nacimiento)
{
    actor_t* actor = malloc(sizeof(actor_t));
    if(actor==NULL)
        return NULL;
    
    strcpy(actor->nombre, nombre);
    actor->nacimiento.anio = nacimiento.anio;
    actor->nacimiento.mes = nacimiento.mes;
    actor->nacimiento.dia = nacimiento.dia;

    return actor;
}

void actor_destruir(actor_t *actor)
{
    free(actor);
}

const char *actor_nombre(const actor_t *actor)
{
    const char* nombre = actor->nombre;
    return nombre;
}

fecha_t actor_nacimiento(const actor_t *actor)
{
    return actor->nacimiento;
}

bool actor_escribir(const actor_t *actor, const char *nombre_archivo)
{
    FILE* ruta=fopen(nombre_archivo, "wb");
    if(ruta ==NULL)
        return false;

    fwrite(&actor->nombre,sizeof(char), NOMBRE_MAX, ruta);
    fwrite(&actor->nacimiento.dia, sizeof(uint8_t), 1, ruta);
    fwrite(&actor->nacimiento.mes, sizeof(uint8_t), 1, ruta);
    fwrite(&actor->nacimiento.anio, sizeof(uint16_t), 1, ruta);

    fclose(ruta);
    return true;
}

actor_t *actor_leer(const char *nombre_archivo)
{
    char nombre[NOMBRE_MAX];
    uint16_t anio;
    uint8_t mes, dia;

    FILE* ruta = fopen(nombre_archivo, "rb");
    if(ruta==NULL)
        return NULL;

    fread(nombre, sizeof(char), NOMBRE_MAX, ruta);
    fread(&dia, sizeof(uint8_t), 1, ruta);
    fread(&mes, sizeof(uint8_t), 1, ruta);
    fread(&anio, sizeof(uint16_t), 1, ruta);

    fecha_t nacimiento = {.dia=dia, .anio=anio, .mes=mes};

    actor_t* actor = actor_crear(nombre, nacimiento);

    fclose(ruta);
    return actor;
}

int fecha_comparar(fecha_t a, fecha_t b)
{
    if(a.anio != b.anio)
        return a.anio - b.anio;
    
    if(a.mes != b.mes)
        return a.mes - b.mes;
    
        return a.dia - b.dia; 
}

static int cmp_actores(const void* a, const void* b)
{
    actor_t **pprim = (actor_t **)a;
    actor_t *prim = *pprim;
    
    actor_t **pseg = (actor_t **)b;
    actor_t *seg = *pseg;

    return fecha_comparar(prim->nacimiento, seg->nacimiento);
    
}

void actores_ordenar_por_fecha_nacimiento(actor_t *actores[], size_t n)
{
    qsort(actores, n , sizeof(actor_t*), cmp_actores);
}

/*static int cmp_nombres(const void* a, const void* b)
{
    actor_t *prim = *((actor_t**) a);
    actor_t *seg = *((actor_t**)b);

    return strcmp(prim->nombre, seg->nombre);
}

actor_t *actores_buscar(actor_t *actores[], size_t n, const char *nombre)
{
    actor_t* actor_buscado = bsearch(&nombre, actores, n, sizeof(actor_t*), cmp_nombres);
    return actor_buscado+1 ;
}*/

actor_t *actores_buscar(actor_t *actores[], size_t n, const char *nombre)
{
    size_t izq=0;
    size_t der = n-1;

    while(izq<=der)
    {
        size_t medio = (izq+der)/2;

        if(!strcmp(actores[medio]->nombre, nombre))
            return actores[medio];
        
        if(strcmp(actores[medio]->nombre, nombre)>0)
        {
            der = medio - 1;
        }else{
            izq = medio + 1;
        }
    }
    return NULL;
}

#define MASK_UNI 0x0000000F
#define MASK_DEC 0x000000F0

#define MASK_UNI_MES 0x00000F00
#define MASK_DEC_MES 0x0000F000
#define MASK_UNI_ANIO 0x000F0000
#define MASK_DEC_ANIO 0x00F00000
#define MASK_CEN_ANIO 0x0F000000
#define MASK_MIL_ANIO 0xF0000000


uint32_t fecha_a_bcd(fecha_t fecha)
{
    uint32_t bcd;

    uint8_t dia_u = fecha.dia %10;
    uint8_t dia_d = fecha.dia /10;

    uint8_t mes_u = fecha.mes %10;
    uint8_t mes_d = fecha.mes /10;

    uint8_t anio_u = fecha.anio %10;
    uint8_t anio_d = (fecha.anio/10) %10;
    uint8_t anio_c = (fecha.anio/100) %10;
    uint8_t anio_m = fecha.anio /1000;

    bcd = (dia_u & MASK_UNI) | ((dia_d & MASK_UNI)<<4) | ((mes_u & MASK_UNI)<<8) | ((mes_d & MASK_UNI)<<12) | ((anio_u & MASK_UNI)<<16) | ((anio_d & MASK_UNI)<<20) | ((anio_c & MASK_UNI)<<24) | ((anio_m & MASK_UNI)<<28);

    return bcd;
}

uint8_t obtener_dia(uint32_t bcd)
{
    uint8_t dia_u = (bcd & MASK_UNI);
    uint8_t dia_d = ((bcd & MASK_DEC)>>4) * 10;

    return dia_u + dia_d;
}

uint8_t obtener_mes(uint32_t bcd)
{
    uint8_t mes_u = (bcd & MASK_UNI_MES)>>8;
    uint8_t mes_d = ((bcd & MASK_DEC_MES)>>12) * 10;

    return mes_u + mes_d;
}

uint16_t obtener_anio(uint32_t bcd)
{
    uint8_t anio_u = ((MASK_UNI_ANIO & bcd) >> 16);
	uint8_t anio_d = ((MASK_DEC_ANIO & bcd) >> 20) * 10;
	uint16_t anio_c = ((MASK_CEN_ANIO & bcd) >> 24) * 100;
	uint16_t anio_m = ((MASK_MIL_ANIO & bcd) >> 28) * 1000;
	return anio_u + anio_d + anio_c + anio_m; 
}

fecha_t bcd_a_fecha(uint32_t bcd)
{
    fecha_t fecha;

    fecha.dia = obtener_dia(bcd);
    fecha.mes = obtener_mes(bcd);
    fecha.anio = obtener_anio(bcd);

    return fecha;
}
