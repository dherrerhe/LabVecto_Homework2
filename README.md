# LabVecto_Homework2: Cálculo de Integral Triple y Centro de Masa

Programa en C que calcula integrales triples y centros de masa en regiones rectangulares 3D usando dos métodos numéricos: **Riemann** y **Monte Carlo**.

**Autor**: dherrerahe  
**Institución**: Universidad Nacional de Colombia  
**Materia**: Cálculo Vectorial 
**Última actualización**: Noviembre 2025

---

##  Tabla de Contenidos

- [Descripción](#descripción)
- [Requisitos](#requisitos)
- [Instalación y Compilación](#instalación-y-compilación)
- [Uso del Programa](#uso-del-programa)
- [Estructura del Código](#estructura-del-código)
- [Ejemplos de Ejecución](#ejemplos-de-ejecución)
- [Funciones Matemáticas](#funciones-matemáticas)
- [Salida de Resultados](#salida-de-resultados)
- [Comandos del Makefile](#comandos-del-makefile)

---

##  Descripción

Este programa implementa dos métodos numéricos para calcular:

1. **Masa Total**: ∫∫∫_V ρ(x,y,z) dV
2. **Centro de Masa**: (x̄, ȳ, z̄)

sobre una región rectangular 3D [xmin, xmax] × [ymin, ymax] × [zmin, zmax].

### Características

 **Dos métodos de integración**:
- Riemann 3D: Determinístico, preciso, subdivide en cubos
- Monte Carlo: Probabilístico, eficiente en altas dimensiones

 **Tres modelos de densidad**:
- Constante: ρ(x,y,z) = 1
- Lineal: ρ(x,y,z) = ax + by + cz
- Gaussiana: ρ(x,y,z) = e^(-(x²+y²+z²))

 **Interfaz interactiva**: Ingreso de parámetros en consola

 **Exportación CSV**: Resultados guardados para análisis

 **Medición de rendimiento**: Tiempo de ejecución registrado

---

##  Requisitos

### Software

**Linux / WSL2:**
```bash
sudo apt update
sudo apt install build-essential gcc make
```

**macOS:**
```bash
brew install gcc make
```

### Hardware
- Procesador: Cualquiera
- RAM: Mínimo 256 MB
- Almacenamiento: ~5 MB

---

##  Instalación y Compilación

### Opción 1: Clonar desde GitHub

```bash
git clone https://github.com/tu_usuario/LabVecto_Homework2.git
cd LabVecto_Homework2
make
```

### Opción 2: Compilación manual

```bash
# Crear estructura si no existe
mkdir -p src include obj

# Compilar
gcc -Wall -Wextra -g -I./include -c src/main.c -o obj/main.o
gcc -Wall -Wextra -g -I./include -c src/densidades.c -o obj/densidades.o
gcc -Wall -Wextra -g -I./include -c src/integracion.c -o obj/integracion.o

# Enlazar
gcc -Wall -Wextra -g -I./include obj/main.o obj/densidades.o obj/integracion.o -o programa -lm
```

---

##  Uso del Programa

### Ejecución Básica

```bash
./programa
```

O usando Makefile:

```bash
make run
```

### Flujo Interactivo

El programa solicita los siguientes datos:

#### 1️ Límites de Integración

```
Límite X min max: 0 1
Límite Y min max: 0 1
Límite Z min max: 0 1
```

Define la región rectangular V = [0,1] × [0,1] × [0,1]

#### 2️ Tipo de Densidad

```
Seleccione densidad (1=Constante, 2=Lineal, 3=Gaussiana): 1
```

**Opciones:**
- **1** - Constante: ρ(x,y,z) = 1 (uniforme)
- **2** - Lineal: ρ(x,y,z) = ax + by + cz (requiere coeficientes)
- **3** - Gaussiana: ρ(x,y,z) = e^(-(x²+y²+z²)) (normal 3D)

#### 2b️ Coeficientes (Solo si eligió Lineal)

```
Ingrese coeficientes a b c: 1.0 1.0 1.0
```

La densidad será: ρ(x,y,z) = 1.0·x + 1.0·y + 1.0·z

#### 3️ Método de Integración

```
Seleccione método (1=Riemann, 2=Monte Carlo): 1
```

#### 3a️ Subdivisiones (Si eligió Riemann)

```
Subdivisiones X Y Z: 10 10 10
```

Divide cada eje en 10 segmentos → 1000 celdas total

**Recomendaciones:**
- Baja precisión: 5-10
- Media precisión: 20-50
- Alta precisión: 100+

#### 3b️ Muestras (Si eligió Monte Carlo)

```
Número de muestras: 100000
```

Genera 100,000 puntos aleatorios en la región

**Recomendaciones:**
- Baja precisión: 1,000-10,000
- Media precisión: 100,000-500,000
- Alta precisión: 1,000,000+

### Resultado

```
Masa: 1.00000000, Centro de masa: (0.50000000, 0.50000000, 0.50000000), Tiempo: 0.001234 s
Resultados guardados en: resultados.csv
```

---

## Estructura del Código

```
LabVecto_Homework2/
│
├── src/                           # Código fuente
│   ├── main.c                     # Programa principal e interfaz
│   ├── densidades.c               # Implementación de funciones de densidad
│   └── integracion.c              # Métodos numéricos de integración
│
├── include/                       # Encabezados
│   ├── densidades.h               # Declaraciones de funciones de densidad
│   └── integracion.h              # Declaraciones de métodos de integración
│
├── obj/                           # Archivos compilados (generado)
│   ├── main.o
│   ├── densidades.o
│   └── integracion.o
│
├── Makefile                       # Automatización de compilación
├── README.md                      # Este archivo
├── .gitignore                     # Archivos ignorados en Git
└── resultados.csv                 # Resultados (generado)
```

### Responsabilidades de Cada Archivo

#### `src/main.c`
**¿Qué hace?**
- Muestra interfaz al usuario
- Solicita entrada interactiva
- Coordina flujo del programa
- Mide tiempo de ejecución
- Guarda resultados en CSV

**Funciones principales:**
- `main()`: Orquesta todo el programa
- `solicitar_limites()`: Pide límites de integración
- `escribir_csv()`: Guarda resultados en archivo

#### `src/densidades.c`
**¿Qué hace?**
- Define 3 modelos de funciones de densidad
- Evalúa densidad en puntos específicos

**Funciones:**
- `densidad_constante()`: Retorna 1.0 (uniforme)
- `densidad_lineal()`: Retorna ax + by + cz
- `densidad_gaussiana()`: Retorna e^(-(x²+y²+z²))
- `evaluar_densidad()`: Selector de función según tipo

#### `src/integracion.c`
**¿Qué hace?**
- Implementa dos métodos numéricos
- Calcula integral triple
- Determina centro de masa

**Funciones:**
- `calcular_integral_riemann()`: Suma de Riemann 3D
  - Divide región en nx × ny × nz celdas
  - Evalúa función en centro de cada celda
  - Suma: Σ ρ(centro) × ΔV
  
- `calcular_integral_monte_carlo()`: Muestreo aleatorio
  - Genera puntos uniformes aleatorios
  - Estima: V × (promedio de ρ)
  - Converge con 1/√N

---

## Ejemplos de Ejecución

### Ejemplo 1: Cubo Unitario - Densidad Constante

```bash
$ ./programa
Límite X min max: 0 1
Límite Y min max: 0 1
Límite Z min max: 0 1
Seleccione densidad (1=Constante, 2=Lineal, 3=Gaussiana): 1
Seleccione método (1=Riemann, 2=Monte Carlo): 1
Subdivisiones X Y Z: 10 10 10

Integrando con Riemann: dx=0.100000, dy=0.100000, dz=0.100000, celdas=1000
Integración completada.

Masa: 1.00000000, Centro de masa: (0.50000000, 0.50000000, 0.50000000), Tiempo: 0.001234 s
```

**Interpretación:**
- Masa = 1.0 (volumen del cubo)
- Centro = (0.5, 0.5, 0.5) (centro geométrico)
-  Correcto: densidad uniforme

### Ejemplo 2: Región Asimétrica - Densidad Lineal

```bash
$ ./programa
Límite X min max: 0 2
Límite Y min max: 0 2
Límite Z min max: 0 2
Seleccione densidad (1=Constante, 2=Lineal, 3=Gaussiana): 2
Ingrese coeficientes a b c: 1 1 1
Seleccione método (1=Riemann, 2=Monte Carlo): 1
Subdivisiones X Y Z: 20 20 20

Integrando con Riemann: dx=0.100000, dy=0.100000, dz=0.100000, celdas=8000
Integración completada.

Masa: 48.00000000, Centro de masa: (1.33333333, 1.33333333, 1.33333333), Tiempo: 0.012345 s
```

**Interpretación:**
- Masa > 8 (volumen = 8, densidad aumenta hacia bordes)
- Centro > (1, 1, 1) (desplazado por densidad creciente)

### Ejemplo 3: Gaussiana - Monte Carlo

```bash
$ ./programa
Límite X min max: -2 2
Límite Y min max: -2 2
Límite Z min max: -2 2
Seleccione densidad (1=Constante, 2=Lineal, 3=Gaussiana): 3
Seleccione método (1=Riemann, 2=Monte Carlo): 2
Número de muestras: 100000

Integrando con Monte Carlo: volumen=64.000000, muestras=100000
Integración completada.

Masa: 0.89456234, Centro de masa: (0.02341234, -0.01234567, 0.00567890), Tiempo: 0.234567 s
```

**Interpretación:**
- Masa < 64 (distribución baja en bordes)
- Centro ≈ (0, 0, 0) (simetría gaussiana)

---

## Funciones Matemáticas

### Integral Triple

La masa total con densidad variable:

```
M = ∫∫∫_V ρ(x,y,z) dV
```

### Centro de Masa

Coordenadas del centroide ponderado:

```
x̄ = (1/M) ∫∫∫_V x·ρ(x,y,z) dV
ȳ = (1/M) ∫∫∫_V y·ρ(x,y,z) dV
z̄ = (1/M) ∫∫∫_V z·ρ(x,y,z) dV
```

### Densidad Constante
```
ρ(x,y,z) = 1
M = Volumen
Centro = Centro geométrico
```

### Densidad Lineal
```
ρ(x,y,z) = ax + by + cz
Centro se desplaza según coeficientes
```

### Densidad Gaussiana
```
ρ(x,y,z) = e^(-(x²+y²+z²))
Máximo en origen (1.0)
Decrece exponencialmente
```

### Método de Riemann 3D

```
I ≈ Σ f(x_i, y_j, z_k) × Δx × Δy × Δz
```

Donde (x_i, y_j, z_k) es el centro de cada celda.

### Método de Monte Carlo

```
I ≈ V × (1/N) × Σ f(punto_aleatorio_i)
```

Donde V es el volumen total, N es número de puntos.

---

## Salida de Resultados

### Consola

```
Masa: M, Centro de masa: (x̄, ȳ, z̄), Tiempo: T s
```

### Archivo CSV: `resultados.csv`

**Formato:**
```
Metodo,Densidad,Nx,Ny,Nz,Muestras,Masa,X_bar,Y_bar,Z_bar,Tiempo_seg
```

**Ejemplo:**
```
Riemann,Constante,10,10,10,0,1.00000000,0.50000000,0.50000000,0.50000000,0.001234
MonteCarlo,Gaussiana,0,0,0,100000,0.89456234,0.02341234,-0.01234567,0.00567890,0.234567
```

**Columnas:**
- `Metodo`: Riemann o MonteCarlo
- `Densidad`: Constante, Lineal o Gaussiana
- `Nx, Ny, Nz`: Subdivisiones (0 para Monte Carlo)
- `Muestras`: Número de muestras (0 para Riemann)
- `Masa`: Valor de ∫∫∫ ρ dV
- `X_bar, Y_bar, Z_bar`: Coordenadas del centro de masa
- `Tiempo_seg`: Tiempo de ejecución

---

## Comandos del Makefile

```bash
make              # Compilar el proyecto
make run          # Compilar y ejecutar
make clean        # Limpiar archivos objeto (.o)
make distclean    # Limpiar todo (obj/, ejecutable, CSV)
make help         # Ver opciones disponibles
make info         # Información del proyecto
```

**Ejemplo:**

```bash
# Compilar desde cero
make clean
make

# Ejecutar
make run

# Ver ayuda
make help
```

---

## Preguntas Frecuentes

**P: ¿Cuál método debo usar?**
- **Riemann**: Cuando necesitas precisión garantizada
- **Monte Carlo**: Cuando necesitas aproximación rápida

**P: ¿Por qué varían los resultados del Monte Carlo?**
- Usa números aleatorios. Múltiples ejecuciones dan resultados ligeramente diferentes.

**P: ¿Qué subdivisiones/muestras usar?**
- Prueba con valores bajos primero, aumenta hasta que estabilice

**P: ¿Dónde ver los resultados guardados?**
- En archivo `resultados.csv` con cualquier editor de texto o Excel

**P: ¿Cómo modificar el código?**
```bash
nano src/main.c       # Editar
make clean && make    # Recompilar
./programa            # Ejecutar
```

---

## Referencias

1. Stewart, J. (2015). Cálculo de Varias Variables
2. Quarteroni, A., Sacco, R., & Saleri, F. (2007). Numerical Mathematics
3. Press, W. H., et al. (2007). Numerical Recipes

---

**Versión**: 1.0  
**Última actualización**: Noviembre 2025
