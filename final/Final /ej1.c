#include <stdio.h>
#include <assert.h>

//no se pq no anda, segui el enunciado 


int buscar(int*v, size_t n, int c)
{
    size_t izq = 0, der = n-1, medio;

    while((v[der] != v[izq]) && (c >= v[izq]) && (c <= v[der]))
    //while(izq<=der)
    {
        medio = izq + ((der-izq)* ((c - v[izq]) / (v[der]-v[izq])) );
        //medio = (izq+der)/2;

        if(v[medio]==c)
            return medio;
        
        if(v[medio]>c)
            der = medio -1;
        
        else
            izq=medio+1;

    }

    return -1;
}

int main(void) {
    // Pruebas con un arreglo de longitud 8
    int numeros[] = {2, 5, 7, 12, 14, 15, 20, 25};
    assert(buscar(numeros, 8, 12) == 3);

    assert(buscar(numeros, 8, 2) == 0);
    assert(buscar(numeros, 8, 25) == 7);
    assert(buscar(numeros, 8, -1) == -1);
    assert(buscar(numeros, 8, 28) == -1);
    assert(buscar(numeros, 8, 21) == -1);

    // OPCIONAL: agregar pruebas.  Sugerencias:
    // * buscar un numero que este al principio del arreglo
    // * buscar un numero que este al final del arreglo
    // * buscar un numero que este repetido en el arreglo (buscar() deberia
    //   devolver el indice de cualquiera de ellos)
    // * buscar un numero x que no este en el arreglo y sea:
    //   * menor que el minimo del arreglo
    //   * mayor que el maximo del arreglo
    //   * entre el minimo y el maximo
    // * repetir las pruebas con un arreglo de longitud 1

    printf("%s: OK\n", __FILE__);
    return 0;
}
