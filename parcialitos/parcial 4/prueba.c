#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
         struct nodo *prim;
     } lista_t;

     struct nodo {
         struct nodo *sig;
         int dato;
};

typedef struct nodo nodo_t;

lista_t *lista_crear()
{
    lista_t* lista = malloc(sizeof(lista_t));
    if(lista==NULL)
        return NULL;
    
    lista->prim = NULL;
    //lista->ultimo = NULL;
    return lista;
}

nodo_t *crear_nodo(int dato, nodo_t* sig)
{
    nodo_t * nodo = malloc(sizeof(nodo_t));
    if(nodo==NULL)
        return NULL;
    
    nodo->sig = sig;
    nodo->dato = dato;

    return nodo;
}

bool lista_insertar_final(lista_t *l, int dato)
{
    nodo_t *nuevo = crear_nodo(dato, NULL);
    if(nuevo==NULL)
        return false;

    if(l->prim == NULL)
    {
        l->prim = nuevo;
        return true;
    }
    
    nodo_t * anterior;
    nodo_t * actual = l->prim;

    while(actual != NULL)
    {
        anterior= actual;
        actual = actual->sig;
    }
    anterior->sig = nuevo;

    return true;
}

void lista_combinar(lista_t *a, lista_t *b)
{
    if(b->prim == NULL)
    {
        free(b);
        return;
    }
    if(a->prim == NULL)
    {
        a->prim = b->prim;
        free(b);
        return;
    }

    nodo_t * actual = a->prim;

    while(actual->sig != NULL)
    {
        actual = actual->sig;
    }

    actual->sig = b->prim;
    free(b);
}

int main(void)
{
    lista_t *a = lista_crear();
    lista_t *b = lista_crear();

    lista_insertar_final(a, 10);
    lista_insertar_final(a, 20);
    lista_insertar_final(a, 30);
    lista_insertar_final(a, 40);

    nodo_t * actual = a->prim;
    /*for(size_t i=0; i<4; i++)
    {
        printf("%i\n", actual->dato);

        actual = actual->sig;
    } */

    lista_insertar_final(b, 5);
    lista_insertar_final(b,6);
    lista_insertar_final(b, 7);
    lista_insertar_final(b, 8);

    /*actual = b->prim;
    for(size_t i=0; i<4; i++)
    {
        printf("%i\n", actual->dato);

        actual = actual->sig;
    } */

    lista_combinar(a, b);

    actual = a->prim;
    for(size_t i=0; i<12; i++)
    {   
        printf("%i\n", actual->dato);

        if(actual->sig == NULL)
        {    
            printf("es null\n");
            break;
        }
        actual = actual->sig;
    }


    return 0;

}