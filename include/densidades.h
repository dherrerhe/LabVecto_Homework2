/*
 * densidades.h
 * Definición de funciones de densidad para diferentes modelos
 */

#ifndef DENSIDADES_H
#define DENSIDADES_H

/*
 * densidad_constante: Densidad uniforme
 * ρ(x,y,z) = 1
 */
double densidad_constante(double x, double y, double z);

/*
 * densidad_lineal: Densidad que varía linealmente
 * ρ(x,y,z) = ax + by + cz
 */
double densidad_lineal(double x, double y, double z, double a, double b, double c);

/*
 * densidad_gaussiana: Densidad con distribución gaussiana
 * ρ(x,y,z) = e^(-(x²+y²+z²))
 */
double densidad_gaussiana(double x, double y, double z);

/*
 * evaluar_densidad: Función wrapper para evaluar cualquier tipo de densidad
 */
double evaluar_densidad(int tipo, double x, double y, double z, double a, double b, double c);

#endif /* DENSIDADES_H */
