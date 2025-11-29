#include "algoritmos.h"
#include "utilidades.h" // Para intercambiar
#include <math.h>       // Para log2
#include <stdlib.h>     // Para malloc/free

// --- Constante para el cambio a Insertion Sort ---
#define LIMITE_INSERCION 16

// ########## INICIO: SECCIÓN DE HEAPSORT (para el peor caso) ##########

// Función para mantener la propiedad de Max-Heap (montículo máximo)
void heapify(int arr[], int n, int i, Metricas* m) {
    int mayor = i;     // Inicializar 'mayor' como la raíz
    int izq = 2 * i + 1; // hijo izquierdo
    int der = 2 * i + 2; // hijo derecho

    // Si el hijo izquierdo es más grande que la raíz
    if (izq < n) {
        m->comparaciones++;
        if (arr[izq] > arr[mayor])
            mayor = izq;
    }

    // Si el hijo derecho es más grande que 'mayor' hasta ahora
    if (der < n) {
        m->comparaciones++;
        if (arr[der] > arr[mayor])
            mayor = der;
    }

    // Si 'mayor' no es la raíz
    if (mayor != i) {
        intercambiar(&arr[i], &arr[mayor], m);
        // Llamar recursivamente a heapify en el sub-árbol afectado
        heapify(arr, n, mayor, m);
    }
}

// Función principal de Heapsort
void ordenamientoHeap(int arr[], int n, Metricas* m) {
    // 1. Construir el Max-Heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, m);
    }

    // 2. Extraer elementos uno por uno
    for (int i = n - 1; i > 0; i--) {
        // Mover la raíz actual (máximo) al final
        intercambiar(&arr[0], &arr[i], m);

        // Llamar a heapify en el montículo reducido
        heapify(arr, i, 0, m);
    }
}

// ########## FIN: SECCIÓN DE HEAPSORT ##########


// ########## INICIO: SECCIÓN DE QUICKSORT (para el caso promedio) ##########

// Función de partición (usando el esquema de Lomuto)
int particion(int arr[], int bajo, int alto, Metricas* m) {
    int pivote = arr[alto]; // Elegir el último elemento como pivote
    int i = (bajo - 1);   // Índice del elemento más pequeño

    for (int j = bajo; j <= alto - 1; j++) {
        // Si el elemento actual es menor o igual al pivote
        m->comparaciones++;
        if (arr[j] <= pivote) {
            i++; // Incrementar índice del elemento pequeño
            intercambiar(&arr[i], &arr[j], m);
        }
    }
    intercambiar(&arr[i + 1], &arr[alto], m);
    return (i + 1);
}

// ########## FIN: SECCIÓN DE QUICKSORT ##########


// ########## INICIO: SECCIÓN DE INTROSORT (El gestor) ##########

// Función recursiva de Introsort
void introsortRecursivo(int arr[], int inicio, int fin, int limiteProfundidad, Metricas* m) {
    int n = fin - inicio + 1;

    // 1. Caso base: Arreglo pequeño, usar Insertion Sort
    if (n <= LIMITE_INSERCION) {
        // Necesitamos llamar a insertion sort en un sub-arreglo
        // Haremos trampa y usaremos la versión completa sobre un puntero
        // Nota: Esto es ineficiente, lo ideal sería un insertion_sort_range
        // pero para este proyecto, usaremos el que ya tenemos.
        if (n > 1) {
             // Llamamos a la función que ya tenemos, pero sobre el "inicio" del sub-arreglo
             // Esta es una simplificación, pasamos (arr + inicio)
             ordenamientoInsercion(arr + inicio, n, m);
        }
        return;
    }

    // 2. Caso de seguridad: Límite de profundidad alcanzado, usar Heapsort
    if (limiteProfundidad == 0) {
        // Heapsort también opera sobre (puntero + inicio)
        ordenamientoHeap(arr + inicio, n, m);
        return;
    }

    // 3. Caso promedio: Usar Quicksort
    // (Podríamos añadir mediana-de-3 aquí, pero usamos pivote simple por facilidad)
    int pivoteIdx = particion(arr, inicio, fin, m);
    
    // Llamadas recursivas
    introsortRecursivo(arr, inicio, pivoteIdx - 1, limiteProfundidad - 1, m);
    introsortRecursivo(arr, pivoteIdx + 1, fin, limiteProfundidad - 1, m);
}

// Función pública que inicia Introsort
void ordenamientoIntro(int arr[], int n, Metricas* m) {
    if (n <= 0) return;
    
    // Calcular el límite de profundidad: 2 * log2(n)
    // Esto es lo que evita el peor caso de Quicksort
    int limite = (int)(2 * log2(n));
    
    introsortRecursivo(arr, 0, n - 1, limite, m);
}