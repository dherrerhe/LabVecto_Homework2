/*
 * densidades.c
 * Implementación de modelos de densidades
 */

#include <math.h>
#include "densidades.h"

/*
 * densidad_constante: Retorna densidad uniforme = 1
 * ρ(x,y,z) = 1
 * 
 * Parámetros:
 *   x, y, z: Coordenadas del punto
 * 
 * Retorna: 1.0 (siempre)
 * 
 * Uso: Para regiones con densidad uniforme
 */
double densidad_constante(double x, double y, double z) {
    (void)x;  /* Evita warning de parámetro no usado */
    (void)y;
    (void)z;
    return 1.0;
}

/*
 * densidad_lineal: Densidad que varía linealmente
 * ρ(x,y,z) = ax + by + cz
 * 
 * Parámetros:
 *   x, y, z: Coordenadas del punto
 *   a, b, c: Coeficientes de la función lineal
 * 
 * Retorna: ax + by + cz
 * 
 * Ejemplo: Si a=1, b=2, c=3 y punto (1,2,3)
 *          ρ = 1*1 + 2*2 + 3*3 = 1 + 4 + 9 = 14
 */
double densidad_lineal(double x, double y, double z, double a, double b, double c) {
    return a * x + b * y + c * z;
}

/*
 * densidad_gaussiana: Distribución gaussiana/normal 3D
 * ρ(x,y,z) = e^(-(x²+y²+z²))
 * 
 * Parámetros:
 *   x, y, z: Coordenadas del punto
 * 
 * Retorna: exp(-(x² + y² + z²))
 * 
 * Propiedades:
 *   - Máximo en origen: ρ(0,0,0) = 1
 *   - Decrece exponencialmente
 *   - Simétrica respecto al origen
 */
double densidad_gaussiana(double x, double y, double z) {
    double r2 = x * x + y * y + z * z;  /* r² = distancia al origen al cuadrado */
    return exp(-r2);
}

/*
 * evaluar_densidad: Función wrapper para evaluar cualquier tipo de densidad
 * 
 * Parámetros:
 *   tipo: Tipo de densidad (1=constante, 2=lineal, 3=gaussiana)
 *   x, y, z: Coordenadas del punto
 *   a, b, c: Coeficientes (usados solo en densidad lineal)
 * 
 * Retorna: El valor de la densidad según el tipo
 */
double evaluar_densidad(int tipo, double x, double y, double z, double a, double b, double c) {
    switch(tipo) {
        case 1:
            /* Densidad constante */
            return densidad_constante(x, y, z);
        case 2:
            /* Densidad lineal */
            return densidad_lineal(x, y, z, a, b, c);
        case 3:
            /* Densidad gaussiana */
            return densidad_gaussiana(x, y, z);
        default:
            /* Si tipo es inválido, retorna constante */
            return 1.0;
    }
}
