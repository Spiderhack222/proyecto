# Proyecto: Benchmarking de Algoritmos de Ordenamiento en C

Este proyecto es un banco de pruebas (benchmark) diseñado para comparar el rendimiento y las características de cuatro algoritmos de ordenamiento, cada uno de una clase de complejidad diferente .

Este proyecto es desarrollado para la clase de Analisis de Algoritmos:
Equipo:
Iván Calderón García
Diego Chavez Ferreira
Leon Maximiliano Guzman Leyva
Maestra: Dra. Violeta Medina Rios 

## 🚀 Algoritmos Implementados

El benchmark evalúa los siguientes 4 algoritmos:

1.  **$O(n^2)$**: `Insertion Sort` (Ordenamiento por Inserción) 
2.  **$O(n \log n)$**: `Merge Sort` (Ordenamiento por Mezcla) 
3.  **$O(n)$ (Lineal)**: `Counting Sort` (Ordenamiento por Conteo) 
4.  **Híbrido**: `Introsort` (Ordenamiento Introductivo) 

## 📂 Estructura del Proyecto

El proyecto está organizado de la siguiente manera:

```
/proyecto/
├── src/                  # Carpeta con todo el código fuente en C 
│   ├── main.c            # El orquestador principal del benchmark
│   ├── algoritmos.h      # Cabeceras de los algoritmos
│   ├── metricas.h        # Estructura para contar métricas
│   ├── utilidades.h      # Cabeceras de los generadores de datos
│   ├── utilidades.c      # Implementación de los generadores
│   ├── ordenamiento_*.c  # Implementación de cada algoritmo
│
├── Makefile              # Archivo para compilar el proyecto 
├── scripts/
│   └── graficar.py       # Script de Python para generar gráficas 
│
├── resultados.csv        # Salida del benchmark con los datos crudos 
├── graficas/             # Carpeta con las gráficas generadas por el script
└── README.md             # Este archivo
```

## 🛠️ Instrucciones de Compilación y Uso

Sigue estos pasos para compilar y ejecutar el benchmark .

### 1. Prerrequisitos

* Un compilador de C (ej. `gcc`)
* La utilidad `make`
* (Opcional, para las gráficas) `python3` y las bibliotecas `pandas`, `matplotlib`, `seaborn`.

### 2. Compilación

Para compilar el proyecto, clona este repositorio (o asegúrate de estar en la carpeta raíz) y simplemente ejecuta `make`:

```bash
make
```
Esto usará el `Makefile` para compilar todos los archivos `.c` de la carpeta `src/` y creará un único ejecutable llamado **`benchmark`** en la carpeta raíz .

### 3. Ejecución del Benchmark

Una vez compilado, ejecuta el programa:

```bash
./benchmark
```

El programa mostrará en la terminal el progreso. Esta operación **puede tardar varios minutos**, ya que está ejecutando todos los algoritmos en todos los tamaños de datos y repeticiones .

Al finalizar, se creará (o sobrescribirá) un archivo llamado **`resultados.csv`** con todas las métricas.

### 4. Generación de Gráficas

El proyecto incluye un script de Python para visualizar los resultados .

Primero, instala las dependencias (solo necesitas hacerlo una vez):
```bash
pip install pandas matplotlib seaborn
```

Luego, ejecuta el script:
```bash
python scripts/graficar.py
```
Esto leerá el archivo `resultados.csv` y creará una carpeta llamada `graficas/` con todas las comparativas en formato `.png` .

### 5. Limpieza

Para eliminar todos los archivos generados por la compilación (los `.o` y el ejecutable `benchmark`), puedes ejecutar:

```bash
make clean
```