import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import os

# --- 1. Configuración ---
ARCHIVO_CSV = "resultados.csv" # Asegúrate que esté en la misma carpeta
CARPETA_GRAFICAS = "graficas"

# Crear la carpeta "graficas" si no existe
if not os.path.exists(CARPETA_GRAFICAS):
    os.makedirs(CARPETA_GRAFICAS)

print(f"Cargando datos desde {ARCHIVO_CSV}...")

# --- 2. Cargar y Procesar los Datos ---
try:
    # Cargar los datos 
    datos = pd.read_csv(ARCHIVO_CSV)

    # Convertir 'NA' en 0 para 'comparaciones' y 'movimientos' 
    # y asegurarse de que sean numéricos
    datos['comparaciones'] = pd.to_numeric(datos['comparaciones'], errors='coerce').fillna(0)
    datos['movimientos'] = pd.to_numeric(datos['movimientos'], errors='coerce').fillna(0)
    datos['time_ms'] = pd.to_numeric(datos['time_ms'], errors='coerce').fillna(0)

    # Calcular la media de las repeticiones 
    # Agrupamos por algoritmo, distribucion y tamano, y calculamos la media del resto
    datos_promedio = datos.groupby(['algoritmo', 'distribucion', 'tamano']).mean(numeric_only=True).reset_index()

    print("Datos cargados y promediados con éxito.")

    # --- 3. Generar Gráficas ---
    
    # Lista de métricas a graficar 
    metricas = ['time_ms', 'comparaciones', 'movimientos']
    
    # Obtenemos la lista de distribuciones únicas
    distribuciones = datos_promedio['distribucion'].unique()

    for dist in distribuciones:
        print(f"Generando gráficas para la distribución: {dist}...")
        
        # Filtramos los datos solo para esta distribución
        datos_dist = datos_promedio[datos_promedio['distribucion'] == dist]
        
        for metrica in metricas:
            
            # No graficar comparaciones para "Conteo" si no tiene
            if metrica == 'comparaciones':
                datos_metrica = datos_dist[datos_dist['algoritmo'] != 'Conteo']
            else:
                datos_metrica = datos_dist

            # Crear la gráfica
            plt.figure(figsize=(10, 6))
            
            # Usamos seaborn para crear una gráfica de líneas 
            # 'hue' dibuja una línea diferente por cada 'algoritmo'
            sns.lineplot(
                data=datos_metrica, 
                x='tamano', 
                y=metrica, 
                hue='algoritmo', 
                style='algoritmo',  # Diferentes estilos de línea
                markers=True,       # Poner marcadores en los puntos
                dashes=False
            )
            
            plt.title(f'{metrica.capitalize()} vs. Tamaño del Arreglo ({dist.capitalize()})')
            plt.xlabel('Tamaño del Arreglo (n)')
            plt.ylabel(f'{metrica.capitalize()}')
            plt.legend(title='Algoritmo')
            plt.grid(True)
            
            # Guardar la gráfica en la carpeta
            nombre_archivo = f"{CARPETA_GRAFICAS}/{dist}_{metrica}.png"
            plt.savefig(nombre_archivo)
            plt.close() # Cerrar la figura para liberar memoria

    print(f"¡Gráficas generadas y guardadas en la carpeta '{CARPETA_GRAFICAS}'!")

except FileNotFoundError:
    print(f"Error: No se encontró el archivo '{ARCHIVO_CSV}'.")
    print("Asegúrate de haber ejecutado './benchmark' primero.")
except Exception as e:
    print(f"Ocurrió un error: {e}")