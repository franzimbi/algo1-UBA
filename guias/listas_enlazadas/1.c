#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    void* dato;
    struct nodo* proximo;
}nodo_t;

typedef struct{
    nodo_t * primero;
}lista_t;

lista_t *lista_crear()
{
    lista_t* lista = malloc(sizeof(lista_t));
    if(lista==NULL)
        return NULL;
    
    lista->primero = NULL;
    //lista->ultimo = NULL;
    return lista;
}

nodo_t *crear_nodo(void* dato, nodo_t proximo)
{
    nodo_t * nodo = malloc(sizeof(nodo_t));
    if(nodo==NULL)
        return NULL;
    
    nodo->proximo = proximo;
    nodo->dato = dato;

    return nodo;
}

void lista_destruir(lista_t *l, void (*destruir_dato)(void *dato))
{
    nodo_t *actual = l->primero;

    while(actual!=NULL)
    {
        nodo_t *sig = actual->siguiente;

        if(destruir_dato !=NULL)
            destruir_dato(actual->dato);
        
        free(actual);
        actual = sig;
    }
}

bool lista_es_vacia(const lista_t *l)
{
    if(l->primero == NULL)
        return true;
    
    return false;
}

bool lista_insertar_comienzo(lista_t *l, void *dato)
{
    nodo_t *nuevo = crear_nodo(dato, l->primero);
        if(nuevo==NULL)
            return false;

    l->primero = nuevo;

    return true;
}

bool lista_insertar_final(lista_t *l, void *dato)
{
    nodo_t *nuevo = crear_nodo(dato, NULL);
    if(nuevo==NULL)
        return false;

    if(l->primero == NULL)
    {
        l->primero = nuevo;
        return true;
    }
    
    nodo_t * anterior;
    nodo_t * actual = l->primero;

    while(actual != NULL)
    {
        anterior= actual;
        actual = actual->proximo;
    }
    anterior->proximo = nuevo;

    return true;
}

void *lista_extraer_primero(lista_t *l)
{

nodo_t *actual = l->primero;
void* dato = NULL;

    if(actual != NULL)
    {
        l->primero = l->primero->proximo;
        dato = actual->dato;

    }

    free(actual);
    return dato;
}

void *lista_extraer_ultimo(lista_t *l)
{
    if(l->proximo ==NULL)
        return NULL;
    
    nodo_t * actual = l->primero;
    nodo_t *anterior=NULL;

    while(actual->proximo != NULL)
    {
        anterior = actual;
        actual= actual->proximo;
    }

    void* dato = actual->dato;
    free(actual);
    
    if(anterior == NULL)
        l->proximo = NULL;
    else
    anterior->proximo = NULL;

    return dato;
}

void *lista_buscar(const lista_t *l, const void *dato, int (*cmp)(const void *a, const void *b))
{
    nodo_t * actual = l->primero;

    while(actual != NULL)
    {
        if(cmp(actual->dato, dato)==0)
            return actual->dato;
        
        actual = actual->proximo;
    }

    return NULL;
}

void *lista_borrar(lista_t *l, const void *dato, int (*cmp)(const void *a, const void *b))
{
    if(l->primero==NULL)
        return NULL;
    
    nodo_t * actual = l->primero;
    nodo * anterior = NULL;

    while(actual != NULL)
    {
        
        if(cmp(actual->dato, dato)==0)
        {
            void* dato = actual->dato;
            if(anterior!=NULL)
            anterior->proximo = actual->proximo;
            else
            l->primero = actual->proximo;

            free(actual);
            return dato;
        }
        anterior = actual;
        actual= actual->proximo;

    }

return NULL;
}

void lista_recorrer(const lista_t *l, bool (*visitar)(void *dato, void *extra), void *extra)
{
    if(l->primero ==NULL)
        return NULL;

    nodo_t * actual = actual->proximo;

    while(actual!=NULL)
    {
        if(!visitar(actual->dato, extra))
        {
            return;
        }

        actual = actual->proximo;
    }
}

void lista_mapear(lista_t *l, void *(*f)(void *dato, void *extra), void *extra)
{
    nodo_t * actual= l->proximo;

    while(actual!=NULL)
    {
        actual->dato = f(actual->dato, extra);
        actual= actual->proximo;
    }
}

lista_t *lista_filtrar(lista_t *l, bool (*f)(void *dato, void *extra), void *extra)
{
    if(l->primero ==NULL)
        return NULL;
    lista_t * nueva_lista = lista_crear();

    nodo_t * actual = l->primero;

    while(actual!=NULL)
    {
        if(f(actual->dato, extra)==true)
        {
            
        }
    }
}