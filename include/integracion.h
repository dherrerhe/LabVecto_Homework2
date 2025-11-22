/*
 * integracion.h
 * Métodos numéricos de integración triple en C
 * 1. Riemann: subdivisión en cubos, preciso y determinístico
 * 2. Monte Carlo: muestreo aleatorio, eficiente en dimensiones altas
 *
 * Ambos calculan:
 *   - Masa: ∫∫∫ ρ dV
 *   - Centro de masa: x̄, ȳ, z̄
 */

#ifndef INTEGRACION_H
#define INTEGRACION_H

/*
 * calcular_integral_riemann:
 * Integra una función ρ(x,y,z) en un volumen usando suma de Riemann.
 * Preciso y determinístico; útil para funciones suaves.
 * Parámetros: límites, tipo de densidad, coeficientes, subdivisiones, punteros a resultados.
 */
void calcular_integral_riemann(double xmin, double xmax, double ymin, double ymax, double zmin, double zmax,
                               int densidad_tipo, double a, double b, double c,
                               int nx, int ny, int nz,
                               double *masa, double *x_bar, double *y_bar, double *z_bar);

/*
 * calcular_integral_monte_carlo:
 * Integra una función ρ(x,y,z) mediante N puntos aleatorios.
 * Eficiente en dimensiones altas; resultado probabilístico.
 * Parámetros: límites, tipo de densidad, coeficientes, número de muestras, punteros a resultados.
 */
void calcular_integral_monte_carlo(double xmin, double xmax, double ymin, double ymax, double zmin, double zmax,
                                   int densidad_tipo, double a, double b, double c,
                                   int muestras,
                                   double *masa, double *x_bar, double *y_bar, double *z_bar);

#endif /* INTEGRACION_H */

