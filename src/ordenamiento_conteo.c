#include "algoritmos.h"
#include <stdlib.h> // Para malloc y free
#include <stdio.h>  // Para printf (en caso de error)
#include <string.h> // Para memset

// Función auxiliar para encontrar el valor máximo en un arreglo
int encontrarMaximo(int arr[], int n) {
    if (n <= 0) return 0;
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

void ordenamientoConteo(int arr[], int n, Metricas* m) {
    if (n <= 0) return;

    // 1. Encontrar el valor máximo para saber el tamaño del arreglo de conteo
    int maximo = encontrarMaximo(arr, n);

    // Crear arreglo de conteo (tamaño maximo + 1)
    // Usamos calloc para inicializarlo todo en 0
    int* conteo = (int*)calloc(maximo + 1, sizeof(int));

    // Crear arreglo de salida
    int* salida = (int*)malloc(n * sizeof(int));

    if (conteo == NULL || salida == NULL) {
        fprintf(stderr, "Error: Falla de malloc en Counting Sort\n");
        free(conteo);
        free(salida);
        return;
    }

    // 2. Almacenar el conteo de cada elemento
    for (int i = 0; i < n; i++) {
        conteo[arr[i]]++;
    }

    // 3. Modificar el arreglo de conteo para que muestre la posición final
    for (int i = 1; i <= maximo; i++) {
        conteo[i] += conteo[i - 1];
    }

    // 4. Construir el arreglo de salida
    // Se itera en reversa para mantener la estabilidad 
    for (int i = n - 1; i >= 0; i--) {
        salida[conteo[arr[i]] - 1] = arr[i];
        m->movimientos++; // Contar movimiento [arr -> salida]
        conteo[arr[i]]--;
    }

    // 5. Copiar el arreglo de salida al arreglo original 'arr'
    for (int i = 0; i < n; i++) {
        arr[i] = salida[i];
        m->movimientos++; // Contar movimiento [salida -> arr]
    }

    // 6. Liberar memoria
    free(conteo);
    free(salida);
}