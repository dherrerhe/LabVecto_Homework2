/*
 * Proyecto: Cálculo Vectorial Computacional
 * Integral Triple y Centro de Masa
 * Archivo: main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "densidades.h"
#include "integracion.h"

#define CSV_OUTPUT "resultados.csv"

/* Prototipos */
void solicitar_limites(double *xmin, double *xmax, double *ymin, double *ymax, double *zmin, double *zmax);
void escribir_csv(const char *metodo, int densidad_tipo, double a, double b, double c,
                   int nx, int ny, int nz, int muestras,
                   double masa, double x_bar, double y_bar, double z_bar, double tiempo);

int main(void) {
    double xmin, xmax, ymin, ymax, zmin, zmax;
    double masa, x_bar, y_bar, z_bar;
    double tiempo_inicio, tiempo_fin, tiempo_ejecucion;
    int metodo, densidad_tipo, nx, ny, nz, muestras;
    double a = 1.0, b = 1.0, c = 1.0;

    /* Solicitar límites */
    solicitar_limites(&xmin, &xmax, &ymin, &ymax, &zmin, &zmax);

    /* Tipo de densidad */
    printf("Seleccione densidad (1=Constante, 2=Lineal, 3=Gaussiana): ");
    scanf("%d", &densidad_tipo);
    if(densidad_tipo == 2) {
        printf("Ingrese coeficientes a b c: ");
        scanf("%lf %lf %lf", &a, &b, &c);
    }

    /* Método de integración */
    printf("Seleccione método (1=Riemann, 2=Monte Carlo): ");
    scanf("%d", &metodo);

    /* Crear CSV si no existe */
    FILE *csv_file = fopen(CSV_OUTPUT, "r");
    if(!csv_file) {
        csv_file = fopen(CSV_OUTPUT, "w");
        fprintf(csv_file, "Metodo,Densidad,Nx,Ny,Nz,Muestras,Masa,X_bar,Y_bar,Z_bar,Tiempo_seg\n");
        fclose(csv_file);
    } else fclose(csv_file);

    /* Ejecución */
    if(metodo == 1) {
        printf("Subdivisiones X Y Z: ");
        scanf("%d %d %d", &nx, &ny, &nz);
        muestras = 0;

        tiempo_inicio = (double)clock()/CLOCKS_PER_SEC;
        calcular_integral_riemann(xmin, xmax, ymin, ymax, zmin, zmax,
                                  densidad_tipo, a, b, c, nx, ny, nz,
                                  &masa, &x_bar, &y_bar, &z_bar);
        tiempo_fin = (double)clock()/CLOCKS_PER_SEC;
    } else {
        printf("Número de muestras: ");
        scanf("%d", &muestras);
        nx = ny = nz = 0;

        tiempo_inicio = (double)clock()/CLOCKS_PER_SEC;
        calcular_integral_monte_carlo(xmin, xmax, ymin, ymax, zmin, zmax,
                                      densidad_tipo, a, b, c, muestras,
                                      &masa, &x_bar, &y_bar, &z_bar);
        tiempo_fin = (double)clock()/CLOCKS_PER_SEC;
    }

    tiempo_ejecucion = tiempo_fin - tiempo_inicio;

    /* Mostrar resultados resumidos */
    printf("\nMasa: %.8f, Centro de masa: (%.8f, %.8f, %.8f), Tiempo: %.6f s\n",
           masa, x_bar, y_bar, z_bar, tiempo_ejecucion);

    /* Guardar en CSV */
    escribir_csv((metodo==1)?"Riemann":"MonteCarlo",
                 densidad_tipo, a, b, c, nx, ny, nz, muestras,
                 masa, x_bar, y_bar, z_bar, tiempo_ejecucion);

    return 0;
}

/* Solicitar límites de integración */
void solicitar_limites(double *xmin, double *xmax, double *ymin, double *ymax, double *zmin, double *zmax) {
    printf("Límite X min max: ");
    scanf("%lf %lf", xmin, xmax);
    printf("Límite Y min max: ");
    scanf("%lf %lf", ymin, ymax);
    printf("Límite Z min max: ");
    scanf("%lf %lf", zmin, zmax);
}

/* Guardar resultados en CSV */
void escribir_csv(const char *metodo, int densidad_tipo, double a, double b, double c,
                   int nx, int ny, int nz, int muestras,
                   double masa, double x_bar, double y_bar, double z_bar, double tiempo) {

    FILE *csv_file = fopen(CSV_OUTPUT, "a");
    if(!csv_file) return;

    const char *densidad_str = (densidad_tipo==1)?"Constante":
                               (densidad_tipo==2)?"Lineal":"Gaussiana";

    fprintf(csv_file, "%s,%s,%d,%d,%d,%d,%.8f,%.8f,%.8f,%.8f,%.6f\n",
            metodo, densidad_str, nx, ny, nz, muestras,
            masa, x_bar, y_bar, z_bar, tiempo);

    fclose(csv_file);
}

