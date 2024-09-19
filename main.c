#include <stdio.h>
#include <math.h>
#include <sys/time.h>

double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0)
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

// Algoritmo fib1: Recursivo con O(2^n)
int fib1(int n) {
    if (n < 2) return n;
    return fib1(n - 1) + fib1(n - 2);
}

// Algoritmo fib2: Iterativo con O(n)
int fib2(int n) {
    int i = 1, j = 0, k;
    for (k = 1; k <= n; k++) {
        int temp = i;
        i = i + j;
        j = temp;
    }
    return j;
}

// Algoritmo fib3: Algoritmo de multiplicación de matrices con O(log n)
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

// Función para calcular los tiempos y generar la tabla
void calcularTiempos(int (*funct)(int), const char* nombre, int* valores_n, int tam) {
    double t0, t1, tf;
    int k = 1000;

    printf("\nTiempos para %s\n", nombre);
    printf("%10s%15s%25s%25s%25s\n", "n", "t(n)", "t(n)/sqrt(log(n))", "t(n)/log(n)", "t(n)/n^0.5");

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
            printf("(*) %8d %15.3f %25.6f %25.6f %25.6f\n", n, tf, tf / sqrt(log(n)), tf / log(n), tf / pow(n, 0.5));
        } else {
            printf("    %8d %15.3f %25.6f %25.6f %25.6f\n", n, tf, tf / sqrt(log(n)), tf / log(n), tf / pow(n, 0.5));
        }
    }
}

int main() {
    // Valores para evaluar en fib1, fib2 y fib3
    int valores_n_fib1[] = {2, 4, 8, 16, 32};  // Valores pequeños para fib1 (recursivo)
    int valores_n_fib2_y_fib3[] = {1000, 10000, 100000, 1000000, 10000000};  // Valores para fib2 y fib3

    // Imprimir tabla para fib1
    calcularTiempos(fib1, "fib1 (recursivo)", valores_n_fib1, 5);

    // Imprimir tabla para fib2
    calcularTiempos(fib2, "fib2 (iterativo)", valores_n_fib2_y_fib3, 5);

    // Imprimir tabla para fib3
    calcularTiempos(fib3, "fib3 (multiplicación de matrices)", valores_n_fib2_y_fib3, 5);

    return 0;
}
