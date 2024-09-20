#include <stdio.h>
#include <math.h>
#include <sys/time.h>

// Función que obtiene el tiempo en microsegundos
double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0)
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

// Algoritmo fib1
int fib1(int n) {
    if (n < 2) return n;
    return fib1(n - 1) + fib1(n - 2);
}

// Algoritmo fib2
int fib2(int n) {
    int i = 1, j = 0, k;
    for (k = 1; k <= n; k++) {
        int temp = i;
        i = i + j;
        j = temp;
    }
    return j;
}

// Algoritmo fib3
int fib3(int n) {
    int i, j, k, h, t;
    i = 1; j = 0; k = 0; h = 1;
    while (n > 0) {
        if ((n % 2) != 0) {
            t = j * h;
            j = (i * h) + (j * k) + t;
            i = (i * k) + t;
        }
        t = h * h;
        h = (2 * k * h) + t;
        k = (k * k) + t;
        n = n / 2;
    }
    return j;
}

// Función para calcular los tiempos y generar la tabla de acuerdo a los exponentes
void tTiempos(int (*funct)(int), double exp1, double exp2, double exp3, int* valores_n, int tam) {
    double t0, t1, tf;
    int k = 1000;

    for (int i = 0; i < tam; i++) {
        int n = valores_n[i];
        t0 = microsegundos();
        funct(n);
        t1 = microsegundos();
        tf = t1 - t0;

        if (tf < 500) {  // Ajuste si el tiempo es demasiado pequeño
            t0 = microsegundos();
            for (int j = 0; j < k; j++) {
                funct(n);
            }
            t1 = microsegundos();
            tf = (t1 - t0) / k;
            printf("(*) %8d %15.3f %19.6f %15.6f %16.6f\n", n, tf, tf / pow(n, exp1), tf / pow(n, exp2), tf / pow(n, exp3));
        } else {
            printf("    %8d %15.3f %19.6f %15.6f %16.6f\n", n, tf, tf / pow(n, exp1), tf / pow(n, exp2), tf / pow(n, exp3));
        }
    }
}

// Función para imprimir las tablas de los tiempos de los algoritmos
void printTiempos() {
    int valores_n_fib1[] = {2, 4, 8, 16, 32};
    int valores_n_fib2_y_fib3[] = {1000, 10000, 100000, 1000000, 10000000};

    // Tabla para fib1 (recursivo)
    printf(" (fib1)\n");
    printf("\n%8s%15s%19s%15s%16s\n", "n", "t(n)", "t(n)/n^1.8", "t(n)/n^2", "t(n)/n^2.2");
    tTiempos(fib1, 1.8, 2, 2.2, valores_n_fib1, 5);

    // Tabla para fib2 (iterativo)
    printf(" (fib2)\n");
    printf("\n%8s%15s%19s%15s%16s\n", "n", "t(n)", "t(n)/n^0.8", "t(n)/n^1", "t(n)/n^1.2");
    tTiempos(fib2, 0.8, 1, 1.2, valores_n_fib2_y_fib3, 5);

    // Tabla para fib3 (multiplicación de matrices)
    printf(" (fib3)\n");
    printf("\n%8s%15s%19s%15s%16s\n", "n", "t(n)", "t(n)/n^0.5", "t(n)/n^0.7", "t(n)/n^0.9");
    tTiempos(fib3, 0.5, 0.7, 0.9, valores_n_fib2_y_fib3, 5);
}

int main() {
    printTiempos();
    return 0;
}
