#include "algoritmos.h"
#include <stdlib.h> // Para malloc y free

// Función auxiliar para mezclar dos sub-arreglos
void mezclar(int arr[], int izq, int med, int der, Metricas* m) {
    int i, j, k;
    int n1 = med - izq + 1;
    int n2 = der - med;

    // Crear arreglos temporales
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    // 1. Copiar datos a los arreglos temporales L[] y R[]
    for (i = 0; i < n1; i++) {
        L[i] = arr[izq + i];
        m->movimientos++; // Contar movimiento [arr -> L]
    }
    for (j = 0; j < n2; j++) {
        R[j] = arr[med + 1 + j];
        m->movimientos++; // Contar movimiento [arr -> R]
    }

    // --- Inicio de la mezcla (Merge) ---
    i = 0; // Índice inicial del primer sub-arreglo (L)
    j = 0; // Índice inicial del segundo sub-arreglo (R)
    k = izq; // Índice inicial del arreglo mezclado (arr)

    while (i < n1 && j < n2) {
        // Esta es la comparación principal
        m->comparaciones++; 
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            m->movimientos++; // Contar movimiento [L -> arr]
            i++;
        } else {
            arr[k] = R[j];
            m->movimientos++; // Contar movimiento [R -> arr]
            j++;
        }
        k++;
    }

    // 2. Copiar los elementos restantes de L[], si hay alguno
    while (i < n1) {
        arr[k] = L[i];
        m->movimientos++; // Contar movimiento [L -> arr]
        i++;
        k++;
    }

    // 3. Copiar los elementos restantes de R[], si hay alguno
    while (j < n2) {
        arr[k] = R[j];
        m->movimientos++; // Contar movimiento [R -> arr]
        j++;
        k++;
    }

    // Liberar la memoria temporal
    free(L);
    free(R);
}

// Función principal de Merge Sort (recursiva)
void ordenamientoMezcla(int arr[], int izq, int der, Metricas* m) {
    if (izq < der) {
        // Encontrar el punto medio
        int med = izq + (der - izq) / 2;

        // Ordenar la primera y segunda mitad
        ordenamientoMezcla(arr, izq, med, m);
        ordenamientoMezcla(arr, med + 1, der, m);

        // Mezclar las mitades ordenadas
        mezclar(arr, izq, med, der, m);
    }
}