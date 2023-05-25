#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
         struct nodo *prim;
     } lista_ordenada_t;

     struct nodo {
         struct nodo *sig;
         int dato;
};

typedef struct nodo nodo_t;


static size_t lista_tamano(lista_ordenada_t* a)
{
    if(a->prim == NULL)
        return 0;
    
    nodo_t* actual = a->prim;
    size_t i=1;

    while(actual->sig != NULL)
    {
        actual = actual->sig;
        i++;
    }
    return i;
}

void lista_combinar(lista_ordenada_t *a, lista_ordenada_t *b)
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

    if(actual->dato < b->prim->dato)
    {    
        actual->sig = b->prim;
        free(b);
    }
    
    nodo_t * menor = b->prim;
    if (menor->dato < actual->dato)
    {
        while (menor->dato < actual->dato)
        {
            actual = actual->sig;
        }
        

    }
    
}
// es dificil probarlo pq tendria que codear crear_lista, crear_nodo, agregar_a_lista, etc... pero me tengo fe :D


bool esta_ordenado(float v[], size_t n)
{
    if(n==1)
        return true;
    
    if(v[0] > v[1])
        return false;

    return esta_ordenado(v+1, n-1);
}

int comparar(const void *a, const void* b)
{
    return strcmp(a, b);
} //esto fue para probarlo en el main

void *buscar(void *v[], size_t n, const void *e, int (*cmp)(const void *a, const void *b))
{
    for(size_t i=0; i<n; i++)
    {
        if(cmp(v[i], e) == 0)
            return v[i];
    }

    return NULL;
}

int main(void)
{
    float v[] = {};

    if(esta_ordenado(v, 0) == true)
        printf("esta ordenado\n");
    else
        printf("no esta ordenado\n");
    

   /* void *v[4];

    v[0] = malloc(sizeof(char) * 5);
    v[1] = malloc(sizeof(char) * 5);
    v[2] = malloc(sizeof(char) * 6);
    v[3] = malloc(sizeof(char) * 2);

    v[0] = "hola";
    v[1] = "como";
    v[2] = "estas";
    v[3] = "?";

    void* sol = buscar(v, 4, "hola", comparar);

    printf("%s\n", sol);
     */

    return 0;
}
