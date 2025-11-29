#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include "metricas.h" // Incluimos la definición de la estructura

/**
 * @brief Ordena un arreglo usando el algoritmo de Inserción.
 * @param arr El arreglo de enteros a ordenar.
 * @param n El tamaño del arreglo.
 * @param m Un puntero a la estructura Metricas para contar operaciones.
 */
void ordenamientoInsercion(int arr[], int n, Metricas* m);

// Aquí añadiremos luego:
// void ordenamientoMezcla(int arr[], int l, int r, Metricas* m);
// void ordenamientoConteo(int arr[], int n, Metricas* m);
// void ordenamientoIntro(int arr[], int n, Metricas* m);

// ... (código de ordenamientoInsercion) ...

/**
 * @brief Función auxiliar para mezclar dos sub-arreglos ordenados.
 * @param arr El arreglo principal.
 * @param izq Índice izquierdo.
 * @param med Índice medio.
 * @param der Índice derecho.
 * @param m Puntero a la estructura de métricas.
 */
void mezclar(int arr[], int izq, int med, int der, Metricas* m);

/**
 * @brief Ordena un arreglo usando el algoritmo de Mezcla (Merge Sort).
 * @param arr El arreglo de enteros a ordenar.
 * @param izq El índice de inicio (generalmente 0).
 * @param der El índice final (generalmente n-1).
 * @param m Un puntero a la estructura Metricas para contar operaciones.
 */
void ordenamientoMezcla(int arr[], int izq, int der, Metricas* m);

// ... (código de ordenamientoInsercion y ordenamientoMezcla) ...

/**
 * @brief Ordena un arreglo de enteros (no negativos) usando Counting Sort.
 * @param arr El arreglo de enteros a ordenar.
 * @param n El tamaño del arreglo.
 * @param m Un puntero a la estructura Metricas para contar operaciones.
 */
void ordenamientoConteo(int arr[], int n, Metricas* m);

// ... (código de ordenamientoInsercion, Mezcla y Conteo) ...

/**
 * @brief Ordena un arreglo usando el algoritmo híbrido Introsort.
 * @param arr El arreglo de enteros a ordenar.
 * @param n El tamaño del arreglo.
 * @param m Un puntero a la estructura Metricas para contar operaciones.
 */
void ordenamientoIntro(int arr[], int n, Metricas* m);

#endif // ALGORITMOS_H