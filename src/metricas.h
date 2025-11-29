#ifndef METRICAS_H
#define METRICAS_H

// Estructura para almacenar los contadores de métricas
// 
typedef struct {
    long long comparaciones;
    long long movimientos; // Incluye tanto swaps como desplazamientos
} Metricas;

#endif // METRICAS_H