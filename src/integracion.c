/*
 * integracion.c
 * Implementación de métodos numéricos de integración triple:
 * - Riemann 3D: subdivisión en cubos, preciso y determinístico
 * - Monte Carlo: puntos aleatorios, eficiente en dimensiones altas
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "integracion.h"
#include "densidades.h"

/* calcular_integral_riemann:
 * Integra ρ(x,y,z) usando suma de Riemann en subceldas.
 * Calcula masa total y centro de masa.
 */
void calcular_integral_riemann(double xmin, double xmax, double ymin, double ymax, double zmin, double zmax,
                               int densidad_tipo, double a, double b, double c,
                               int nx, int ny, int nz,
                               double *masa, double *x_bar, double *y_bar, double *z_bar) {
    double dx = (xmax - xmin) / nx;
    double dy = (ymax - ymin) / ny;
    double dz = (zmax - zmin) / nz;
    double dV = dx * dy * dz;

    double integral_masa = 0.0, integral_x = 0.0, integral_y = 0.0, integral_z = 0.0;
    double rho;

    printf("Integrando con Riemann: dx=%.6f, dy=%.6f, dz=%.6f, celdas=%d\n", dx, dy, dz, nx*ny*nz);

    for (int i = 0; i < nx; i++)
        for (int j = 0; j < ny; j++)
            for (int k = 0; k < nz; k++) {
                double x = xmin + (i + 0.5) * dx;
                double y = ymin + (j + 0.5) * dy;
                double z = zmin + (k + 0.5) * dz;

                rho = evaluar_densidad(densidad_tipo, x, y, z, a, b, c);

                integral_masa += rho * dV;
                integral_x += x * rho * dV;
                integral_y += y * rho * dV;
                integral_z += z * rho * dV;
            }

    *masa = integral_masa;
    if (integral_masa > 1e-10) {
        *x_bar = integral_x / integral_masa;
        *y_bar = integral_y / integral_masa;
        *z_bar = integral_z / integral_masa;
    } else {
        *x_bar = *y_bar = *z_bar = 0.0;
    }

    printf("Integración completada.\n");
}

/* calcular_integral_monte_carlo:
 * Integra ρ(x,y,z) usando N puntos aleatorios.
 * Calcula masa total y centro de masa.
 */
void calcular_integral_monte_carlo(double xmin, double xmax, double ymin, double ymax, double zmin, double zmax,
                                   int densidad_tipo, double a, double b, double c,
                                   int muestras,
                                   double *masa, double *x_bar, double *y_bar, double *z_bar) {
    double volumen = (xmax - xmin) * (ymax - ymin) * (zmax - zmin);

    double suma_densidad = 0.0, suma_x_densidad = 0.0, suma_y_densidad = 0.0, suma_z_densidad = 0.0;
    double rho;

    printf("Integrando con Monte Carlo: volumen=%.6f, muestras=%d\n", volumen, muestras);

    srand(42);  // semilla fija

    for (int i = 0; i < muestras; i++) {
        double x = xmin + (double)rand()/RAND_MAX * (xmax - xmin);
        double y = ymin + (double)rand()/RAND_MAX * (ymax - ymin);
        double z = zmin + (double)rand()/RAND_MAX * (zmax - zmin);

        rho = evaluar_densidad(densidad_tipo, x, y, z, a, b, c);

        suma_densidad += rho;
        suma_x_densidad += x * rho;
        suma_y_densidad += y * rho;
        suma_z_densidad += z * rho;
    }

    double integral_masa = suma_densidad / muestras * volumen;
    double integral_x = suma_x_densidad / muestras * volumen;
    double integral_y = suma_y_densidad / muestras * volumen;
    double integral_z = suma_z_densidad / muestras * volumen;

    *masa = integral_masa;
    if (integral_masa > 1e-10) {
        *x_bar = integral_x / integral_masa;
        *y_bar = integral_y / integral_masa;
        *z_bar = integral_z / integral_masa;
    } else {
        *x_bar = *y_bar = *z_bar = 0.0;
    }

    printf("Integración completada.\n");
}

