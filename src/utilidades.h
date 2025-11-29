#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <stdlib.h> // Para size_t

/**
 * @brief Genera un arreglo de 'n' enteros con valores aleatorios uniformes.
 * @param n Tamaño del arreglo.
 * @return Puntero al arreglo generado dinámicamente.
 */
int* generarDatosUniforme(int n); // 

/**
 * @brief Genera un arreglo de 'n' enteros ordenados ascendentemente.
 * @param n Tamaño del arreglo.
 * @return Puntero al arreglo generado dinámicamente.
 */
int* generarDatosOrdenados(int n); // 

/**
 * @brief Genera un arreglo de 'n' enteros ordenados descendentemente.
 * @param n Tamaño del arreglo.
 * @return Puntero al arreglo generado dinámicamente.
 */
int* generarDatosReversos(int n); // 

/**
 * @brief Genera un arreglo 'casi ordenado' (pocas permutaciones).
 * @param n Tamaño del arreglo.
 * @return Puntero al arreglo generado dinámicamente.
 */
int* generarDatosCasiOrdenados(int n); // 

/**
 * @brief Genera un arreglo con muchos valores duplicados.
 * @param n Tamaño del arreglo.
 * @return Puntero al arreglo generado dinámicamente.
 */
int* generarDatosDuplicados(int n); // 

/**
 * @brief Copia un arreglo 'origen' en un arreglo 'destino'.
 * @param origen Arreglo fuente.
 * @param destino Arreglo destino (debe tener memoria asignada).
 * @param n Tamaño de los arreglos.
 */
void copiarArreglo(int origen[], int destino[], int n);

/**
 * @brief Imprime los elementos de un arreglo en la consola.
 * @param arr Arreglo a imprimir.
 * @param n Tamaño del arreglo.
 */
void imprimirArreglo(int arr[], int n);

// ... (resto de funciones) ...

#include "metricas.h" // Asegurarse de que esté incluido

/**
 * @brief Intercambia dos valores enteros y cuenta la operación.
 * @param a Puntero al primer entero.
 * @param b Puntero al segundo entero.
 * @param m Puntero a la estructura de métricas.
 */
void intercambiar(int* a, int* b, Metricas* m);

#endif // UTILIDADES_H