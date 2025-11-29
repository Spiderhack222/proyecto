#include <stdio.h>
#include <stdlib.h> // Para malloc, free, srand
#include <time.h>   // Para time

#include "algoritmos.h"
#include "metricas.h"
#include "utilidades.h" // Incluimos las utilidades

int main() {
    // --- INICIALIZACIÓN ---
    // Inicializar el generador de números aleatorios UNA SOLA VEZ
    // al inicio del programa.
    srand(time(NULL));

    printf("--- Prueba del Banco de Pruebas (Benchmark) ---\n");

    // 1. Definimos parámetros de la prueba
    //    Usamos un tamaño pequeño (ej. 20) solo para esta prueba inicial.
    //    En el benchmark final, esto será un bucle con los tamaños
    //    del proyecto (100, 200, 500...) 
    int n = 20; 
    
    // 2. Generamos el arreglo "maestro" u "original"
    //    Probemos con el generador "casi ordenado" 
    int* arreglo_original = generarDatosCasiOrdenados(n);
    
    // Verificación importante: checar si malloc falló
    if (arreglo_original == NULL) {
        fprintf(stderr, "Error al generar datos (malloc falló).\n");
        return 1; // Salir con código de error
    }
    
    printf("Arreglo Original (Casi Ordenado, n=%d):\n", n);
    imprimirArreglo(arreglo_original, n);
    printf("--------------------------------------------\n");

    // --- PRUEBA 1: ORDENAMIENTO POR INSERCIÓN ---
    
    // 3. Creamos una copia para este algoritmo
    //    Es VITAL ordenar una copia, no el original,
    //    para poder usar el mismo arreglo original para otros algoritmos.
    int* copia_para_insercion = (int*)malloc(n * sizeof(int));
    
    if (copia_para_insercion == NULL) {
        fprintf(stderr, "Error al crear copia (malloc falló).\n");
        free(arreglo_original); // Liberar memoria antes de salir
        return 1;
    }
    
    // Copiamos los datos del original a la copia de trabajo
    copiarArreglo(arreglo_original, copia_para_insercion, n);

    // 4. Ejecutamos el algoritmo sobre la COPIA
    Metricas metricas_insercion = {0, 0}; // Inicializar contadores
    printf("Ejecutando Ordenamiento por Inserción...\n");
    
    // Pasamos la dirección de la estructura de métricas
    ordenamientoInsercion(copia_para_insercion, n, &metricas_insercion);
    
    printf("Arreglo ordenado: ");
    imprimirArreglo(copia_para_insercion, n);

    // 5. Reportamos métricas 
    printf("  Comparaciones: %lld\n", metricas_insercion.comparaciones);
    printf("  Movimientos: %lld\n", metricas_insercion.movimientos);
    printf("  Estable: SI\n"); // Insertion Sort es estable

    
    // --- (Aquí irían las pruebas para Merge, Counting, Intro...) ---
    // (Cada una crearía su propia copia de 'arreglo_original')


    // 6. Liberamos la memoria
    //    Debemos liberar TODOS los arreglos creados con malloc
    printf("--------------------------------------------\n");
    printf("Liberando memoria...\n");
    free(arreglo_original);
    free(copia_para_insercion);
    // (Aquí también iría free() para las otras copias)

    printf("Prueba finalizada.\n");

    // ... (Todo el código anterior de "PRUEBA 1: ORDENAMIENTO POR INSERCIÓN") ...
    
    // --- PRUEBA 2: ORDENAMIENTO POR MEZCLA ---
    printf("--------------------------------------------\n");
    
    // 3. Creamos una NUEVA copia para este algoritmo
    int* copia_para_mezcla = (int*)malloc(n * sizeof(int));
    if (copia_para_mezcla == NULL) {
        fprintf(stderr, "Error al crear copia (malloc falló).\n");
        free(arreglo_original);
        free(copia_para_insercion);
        return 1;
    }
    copiarArreglo(arreglo_original, copia_para_mezcla, n);

    // 4. Ejecutamos el algoritmo sobre la COPIA
    Metricas metricas_mezcla = {0, 0}; // Nuevos contadores
    printf("Ejecutando Ordenamiento por Mezcla...\n");
    
    // [IMPORTANTE] Merge Sort se llama con (arr, 0, n-1)
    ordenamientoMezcla(copia_para_mezcla, 0, n - 1, &metricas_mezcla);
    
    printf("Arreglo ordenado: ");
    imprimirArreglo(copia_para_mezcla, n);

    // 5. Reportamos métricas
    printf("  Comparaciones: %lld\n", metricas_mezcla.comparaciones);
    printf("  Movimientos: %lld\n", metricas_mezcla.movimientos);
    printf("  Estable: SI\n"); // Merge Sort es estable

    // 6. Liberamos la memoria
    printf("--------------------------------------------\n");
    printf("Liberando memoria...\n");
    free(arreglo_original);
    free(copia_para_insercion);
    free(copia_para_mezcla); // <-- AÑADIR ESTA LÍNEA

    printf("Prueba finalizada.\n");

    // ... (Todo el código anterior de "PRUEBA 2: ORDENAMIENTO POR MEZCLA") ...

    // --- PRUEBA 3: ORDENAMIENTO POR CONTEO ---
    printf("--------------------------------------------\n");
    
    // 3. Creamos una TERCERA copia
    int* copia_para_conteo = (int*)malloc(n * sizeof(int));
    if (copia_para_conteo == NULL) {
        fprintf(stderr, "Error al crear copia (malloc falló).\n");
        free(arreglo_original);
        free(copia_para_insercion);
        free(copia_para_mezcla);
        return 1;
    }
    copiarArreglo(arreglo_original, copia_para_conteo, n);

    // 4. Ejecutamos el algoritmo sobre la COPIA
    Metricas metricas_conteo = {0, 0}; // Nuevos contadores
    printf("Ejecutando Ordenamiento por Conteo...\n");
    
    ordenamientoConteo(copia_para_conteo, n, &metricas_conteo);
    
    printf("Arreglo ordenado: ");
    imprimirArreglo(copia_para_conteo, n);

    // 5. Reportamos métricas
    // No reportamos comparaciones, ponemos "NA"
    printf("  Comparaciones: NA\n"); 
    printf("  Movimientos: %lld\n", metricas_conteo.movimientos);
    printf("  Estable: SI\n"); // Counting Sort es estable

    // 6. Liberamos la memoria
    printf("--------------------------------------------\n");
    printf("Liberando memoria...\n");
    free(arreglo_original);
    free(copia_para_insercion);
    free(copia_para_mezcla);
    free(copia_para_conteo); // <-- AÑADIR ESTA LÍNEA

    printf("Prueba finalizada.\n");

    // ... (Todo el código anterior de "PRUEBA 3: ORDENAMIENTO POR CONTEO") ...

    // --- PRUEBA 4: ORDENAMIENTO INTROSPECTIVO (INTROSHORT) ---
    printf("--------------------------------------------\n");
    
    // 3. Creamos una CUARTA copia
    int* copia_para_intro = (int*)malloc(n * sizeof(int));
    if (copia_para_intro == NULL) {
        fprintf(stderr, "Error al crear copia (malloc falló).\n");
        free(arreglo_original);
        free(copia_para_insercion);
        free(copia_para_mezcla);
        free(copia_para_conteo);
        return 1;
    }
    copiarArreglo(arreglo_original, copia_para_intro, n);

    // 4. Ejecutamos el algoritmo sobre la COPIA
    Metricas metricas_intro = {0, 0}; // Nuevos contadores
    printf("Ejecutando Ordenamiento Intro (Introsort)...\n");
    
    ordenamientoIntro(copia_para_intro, n, &metricas_intro);
    
    printf("Arreglo ordenado: ");
    imprimirArreglo(copia_para_intro, n);

    // 5. Reportamos métricas
    printf("  Comparaciones: %lld\n", metricas_intro.comparaciones);
    printf("  Movimientos: %lld\n", metricas_intro.movimientos);
    // Introsort (basado en Quicksort/Heapsort) NO es estable
    printf("  Estable: NO\n"); 


    // 6. Liberamos la memoria
    printf("--------------------------------------------\n");
    printf("Liberando memoria...\n");
    free(arreglo_original);
    free(copia_para_insercion);
    free(copia_para_mezcla);
    free(copia_para_conteo);
    free(copia_para_intro); // <-- AÑADIR ESTA LÍNEA

    printf("Prueba finalizada.\n");
    return 0; // Salida exitosa
}