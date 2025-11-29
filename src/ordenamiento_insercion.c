#include "algoritmos.h"

void ordenamientoInsercion(int arr[], int n, Metricas* m) {
    int i, llave, j;
    
    // Empezamos desde el segundo elemento (índice 1)
    for (i = 1; i < n; i++) {
        
        // Guardamos el elemento a insertar
        llave = arr[i];
        // Contamos esto como un "movimiento" (de arr[i] a 'llave')
        m->movimientos++; 
        
        j = i - 1;

        // Comparamos 'llave' con los elementos a su izquierda
        // Este bucle 'while' es el núcleo de las comparaciones
        
        // Incrementamos la comparación ANTES de entrar al bucle
        m->comparaciones++; 
        while (j >= 0 && arr[j] > llave) {
            
            // Desplazamos el elemento mayor a la derecha
            arr[j + 1] = arr[j];
            m->movimientos++; // Contamos el desplazamiento
            
            j = j - 1;
            
            // Si el bucle no ha terminado, significa que haremos otra comparación
            if (j >= 0) {
                 m->comparaciones++;
            }
        }
        
        // Colocamos la 'llave' en su posición correcta
        arr[j + 1] = llave;
        m->movimientos++; // Contamos el "movimiento" (de 'llave' a arr[j+1])
    }
}