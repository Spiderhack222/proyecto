#include "utilidades.h"
#include <stdio.h>
#include <stdlib.h> // Para malloc, rand
#include <time.h>   // Para time (usado en srand)

// Función para imprimir un arreglo
void imprimirArreglo(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Función para copiar un arreglo
void copiarArreglo(int origen[], int destino[], int n) {
    for (int i = 0; i < n; i++) {
        destino[i] = origen[i];
    }
}

// 1. Datos Aleatorios (Uniforme) 
int* generarDatosUniforme(int n) {
    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) return NULL; // Buena práctica: verificar malloc
    
    for (int i = 0; i < n; i++) {
        // Usamos un rango amplio, ej. 0 a n*10
        arr[i] = rand() % (n * 10); 
    }
    return arr;
}

// 2. Datos Ordenados 
int* generarDatosOrdenados(int n) {
    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) return NULL;
    
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1; // [1, 2, 3, ...]
    }
    return arr;
}

// 3. Datos en Reverso 
int* generarDatosReversos(int n) {
    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) return NULL;
    
    for (int i = 0; i < n; i++) {
        arr[i] = n - i; // [n, n-1, n-2, ...]
    }
    return arr;
}

// 4. Datos Casi Ordenados 
int* generarDatosCasiOrdenados(int n) {
    // Empezamos con un arreglo ordenado
    int* arr = generarDatosOrdenados(n);
    if (arr == NULL) return NULL;
    
    // "Pocas permutaciones": intercambiamos un 5% de los elementos
    int permutaciones = (int)(n * 0.05);
    if (permutaciones == 0 && n > 1) {
        permutaciones = 1; // Asegurar al menos 1 swap
    }

    for (int i = 0; i < permutaciones; i++) {
        // Elegir dos índices al azar
        int idx1 = rand() % n;
        int idx2 = rand() % n;
        
        // Intercambiarlos (swap)
        int temp = arr[idx1];
        arr[idx1] = arr[idx2];
        arr[idx2] = temp;
    }
    return arr;
}

// 5. Datos con Duplicados 
int* generarDatosDuplicados(int n) {
    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) return NULL;
    
    // "Muchos repetidos": usamos un rango de valores pequeño
    // Por ejemplo, números aleatorios entre 0 y n/10 (o 10 si n es pequeño)
    int rango = (n > 100) ? (n / 10) : 10;
    
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % rango;
    }
    return arr;
}


// ... (resto de funciones) ...

#include "metricas.h" // Incluir por si acaso

void intercambiar(int* a, int* b, Metricas* m) {
    int temp = *a;
    *a = *b;
    *b = temp;
    
    // Un 'swap' completo cuenta como 3 movimientos
    // (temp = a, a = b, b = temp)
    // O podemos contarlo como 1 "swap".
    // Usemos 3 movimientos para ser consistentes con 'insertion sort'
    // que movía elementos uno por uno.
    m->movimientos += 3;
}