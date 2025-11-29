#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Para clock() y srand() 

#include "algoritmos.h"
#include "metricas.h"
#include "utilidades.h"

// --- 1. Definición de los Experimentos ---

// Nombres de los algoritmos para el CSV
const char* NOMBRES_ALGORITMOS[] = {
    "Insercion",
    "Mezcla",
    "Conteo",
    "Intro"
};
const int NUM_ALGORITMOS = 4;

// Nombres de las distribuciones para el CSV 
const char* NOMBRES_DISTRIBUCIONES[] = {
    "uniforme",     // 
    "ordenado",     // 
    "reverso",      // 
    "casi_ordenado",// 
    "duplicados"    // 
};
const int NUM_DISTRIBUCIONES = 5;

// Tamaños de los arreglos 
// (Ajustados para una prueba rápida, puedes poner los del PDF)
int TAMANOS[] = {100, 200, 500, 1000, 2500, 5000, 7500};
// int TAMANOS[] = {100, 200, 300, 400, 500, 1000, 2500, 5000, 7500}; // 
const int NUM_TAMANOS = sizeof(TAMANOS) / sizeof(TAMANOS[0]);

// Número de repeticiones por experimento 
const int REPETICIONES = 3;


// --- 2. Funciones Auxiliares del Benchmark ---

/**
 * @brief Genera datos según el índice de la distribución.
 * Esto evita un 'if' o 'switch' gigante en el bucle principal.
 */
int* generarDatos(int indice_distribucion, int n) {
    switch (indice_distribucion) {
        case 0: return generarDatosUniforme(n);
        case 1: return generarDatosOrdenados(n);
        case 2: return generarDatosReversos(n);
        case 3: return generarDatosCasiOrdenados(n);
        case 4: return generarDatosDuplicados(n);
        default: return NULL;
    }
}

/**
 * @brief Ejecuta el algoritmo según el índice.
 * También maneja las diferentes firmas de las funciones.
 */
void ejecutarAlgoritmo(int indice_algoritmo, int* arr, int n, Metricas* m) {
    switch (indice_algoritmo) {
        case 0: // Inserción
            ordenamientoInsercion(arr, n, m);
            break;
        case 1: // Mezcla (Merge)
            ordenamientoMezcla(arr, 0, n - 1, m); // [Importante: 0 a n-1]
            break;
        case 2: // Conteo
            ordenamientoConteo(arr, n, m);
            break;
        case 3: // Intro
            ordenamientoIntro(arr, n, m);
            break;
    }
}

/**
 * @brief Obtiene la propiedad de estabilidad (fija) del algoritmo. 
 */
const char* obtenerEstabilidad(int indice_algoritmo) {
    switch (indice_algoritmo) {
        case 0: return "SI"; // Inserción
        case 1: return "SI"; // Mezcla
        case 2: return "SI"; // Conteo
        case 3: return "NO"; // Intro
        default: return "NA";
    }
}


// --- 3. Programa Principal (Main) ---

int main() {
    // Inicializar el generador de números aleatorios
    srand(time(NULL));

    // Abrir el archivo CSV para escribir los resultados 
    FILE* archivo_csv = fopen("resultados.csv", "w");
    if (archivo_csv == NULL) {
        fprintf(stderr, "Error: No se pudo abrir el archivo resultados.csv\n");
        return 1;
    }

    // Escribir la cabecera del CSV 
    fprintf(archivo_csv, "algoritmo,distribucion,tamano,repeticion,time_ms,comparaciones,movimientos,estable\n");

    printf("Iniciando benchmark... Esto puede tardar varios minutos.\n");

    // --- 4. Bucles Anidados del Experimento ---
    
    // Bucle 1: Algoritmos
    for (int idx_algo = 0; idx_algo < NUM_ALGORITMOS; idx_algo++) {
        
        const char* nombre_algo = NOMBRES_ALGORITMOS[idx_algo];
        printf("Probando Algoritmo: %s\n", nombre_algo);

        // Bucle 2: Distribuciones
        for (int idx_dist = 0; idx_dist < NUM_DISTRIBUCIONES; idx_dist++) {
            
            const char* nombre_dist = NOMBRES_DISTRIBUCIONES[idx_dist];
            printf("  Distribucion: %s\n", nombre_dist);

            // Bucle 3: Tamaños
            for (int idx_tam = 0; idx_tam < NUM_TAMANOS; idx_tam++) {
                
                int n = TAMANOS[idx_tam];
                
                // Bucle 4: Repeticiones
                for (int rep = 1; rep <= REPETICIONES; rep++) {
                
                    // --- 5. Ejecución de una Sola Corrida ---

                    // a. Generar datos "originales"
                    int* arreglo_original = generarDatos(idx_dist, n);
                    if (arreglo_original == NULL) {
                        fprintf(stderr, "Error de memoria al generar datos.\n");
                        continue; // Saltar esta corrida
                    }

                    // b. Crear copia de trabajo
                    int* copia_trabajo = (int*)malloc(n * sizeof(int));
                    if (copia_trabajo == NULL) {
                        fprintf(stderr, "Error de memoria al crear copia.\n");
                        free(arreglo_original);
                        continue;
                    }
                    copiarArreglo(arreglo_original, copia_trabajo, n);

                    // c. Inicializar métricas
                    Metricas metricas = {0, 0};

                    // d. Medir el tiempo 
                    clock_t inicio = clock();
                    
                    ejecutarAlgoritmo(idx_algo, copia_trabajo, n, &metricas);
                    
                    clock_t fin = clock();
                    
                    // Calcular tiempo en milisegundos
                    double time_ms = ((double)(fin - inicio) * 1000) / CLOCKS_PER_SEC;

                    // e. Obtener métricas fijas
                    const char* estabilidad = obtenerEstabilidad(idx_algo);

                    // f. Escribir resultados en el CSV
                    
                    // Manejo especial para Conteo (sin comparaciones) 
                    if (idx_algo == 2) { // Índice 2 es "Conteo"
                        fprintf(archivo_csv, "%s,%s,%d,%d,%.4f,NA,%lld,%s\n",
                                nombre_algo, nombre_dist, n, rep,
                                time_ms, metricas.movimientos, estabilidad);
                    } else {
                        fprintf(archivo_csv, "%s,%s,%d,%d,%.4f,%lld,%lld,%s\n",
                                nombre_algo, nombre_dist, n, rep,
                                time_ms, metricas.comparaciones, metricas.movimientos, estabilidad);
                    }

                    // g. Liberar memoria para esta corrida
                    free(arreglo_original);
                    free(copia_trabajo);

                } // Fin bucle repeticiones
            } // Fin bucle tamaños
        } // Fin bucle distribuciones
    } // Fin bucle algoritmos

    // --- 6. Finalización ---
    fclose(archivo_csv);
    printf("¡Benchmark finalizado! Resultados guardados en 'resultados.csv'.\n");

    return 0;
}