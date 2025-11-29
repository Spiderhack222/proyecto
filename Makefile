# --- Regla Principal ---
# Si escribes "make", buscará la regla "all".
# Esta regla depende de "benchmark".
all: benchmark

# --- Regla de Enlace ---
# Para crear el ejecutable "benchmark", necesita todos los .o
# Esta regla junta todos los .o y los enlaza con la librería -lm (matemáticas)
benchmark: src/main.o src/utilidades.o src/ordenamiento_insercion.o src/ordenamiento_mezcla.o src/ordenamiento_conteo.o src/ordenamiento_intro.o
	gcc src/main.o src/utilidades.o src/ordenamiento_insercion.o src/ordenamiento_mezcla.o src/ordenamiento_conteo.o src/ordenamiento_intro.o -o benchmark -lm

# --- Reglas de Compilación (.o) ---
# Cada regla le dice cómo crear un archivo .o a partir de un .c

src/main.o: src/main.c src/algoritmos.h src/metricas.h src/utilidades.h
	gcc -Wall -Wextra -g -O2 -std=c99 -c src/main.c -o src/main.o

src/utilidades.o: src/utilidades.c src/utilidades.h src/metricas.h
	gcc -Wall -Wextra -g -O2 -std=c99 -c src/utilidades.c -o src/utilidades.o

src/ordenamiento_insercion.o: src/ordenamiento_insercion.c src/algoritmos.h
	gcc -Wall -Wextra -g -O2 -std=c99 -c src/ordenamiento_insercion.c -o src/ordenamiento_insercion.o

src/ordenamiento_mezcla.o: src/ordenamiento_mezcla.c src/algoritmos.h
	gcc -Wall -Wextra -g -O2 -std=c99 -c src/ordenamiento_mezcla.c -o src/ordenamiento_mezcla.o

src/ordenamiento_conteo.o: src/ordenamiento_conteo.c src/algoritmos.h
	gcc -Wall -Wextra -g -O2 -std=c99 -c src/ordenamiento_conteo.c -o src/ordenamiento_conteo.o

src/ordenamiento_intro.o: src/ordenamiento_intro.c src/algoritmos.h src/utilidades.h
	gcc -Wall -Wextra -g -O2 -std=c99 -c src/ordenamiento_intro.c -o src/ordenamiento_intro.o

# --- Regla de Limpieza ---
# Se ejecuta con "make clean"
clean:
	rm -f src/main.o src/utilidades.o src/ordenamiento_insercion.o src/ordenamiento_mezcla.o src/ordenamiento_conteo.o src/ordenamiento_intro.o benchmark