#include <stdio.h>
#include <math.h>
#include <sys/time.h>

double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0)
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

int fib1(int n) {
    if (n < 2) return n;
    return fib1(n - 1) + fib1(n - 2);
}

// Algoritmo fib2: Iterativo com O(n)
int fib2(int n) {
    int i = 1, j = 0, k;
    for (k = 1; k <= n; k++) {
        int temp = i;
        i = i + j;
        j = temp;
    }
    return j;
}

// Algoritmo fib3: Algoritmo de multiplicação de matrizes com O(log n)
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
void calcularTiempos(int (*funct)(int), double x, double y, double z) {
    double t0, t1, tf;
    int n;
    int k = 1000;

    printf("%8s%15s%15s%15s%15s\n", "n", "t(n)", "t(n)/sqrt(log(n))", "t(n)/log(n)", "t(n)/n^0.5");

    for (n = 2; n <= 32; n = n * 2) {
        t0 = microsegundos();
        funct(n);
        t1 = microsegundos();
        tf = t1 - t0;

        if (tf < 500) {  // Ajuste si el tiempo es demasiado pequeño
            t0 = microsegundos();
            for (int i = 0; i < k; i++) {
                funct(n);
            }
            t1 = microsegundos();
            tf = (t1 - t0) / k;
            printf("(*) %5d %15.3f %15.6f %15.6f %15.6f\n", n, tf, tf / sqrt(log(n)), tf / log(n), tf / pow(n, 0.5));
        } else {
            printf("    %5d %15.3f %15.6f %15.6f %15.6f\n", n, tf, tf / sqrt(log(n)), tf / log(n), tf / pow(n, 0.5));
        }
    }
}

int main() {
    // Imprimir tabla para fib1
    printf("Tiempos para fib1 (recursivo)\n");
    calcularTiempos(fib1, sqrt(log(2)), log(2), pow(2, 0.5));

    // Imprimir tabla para fib2
    printf("\nTiempos para fib2 (iterativo)\n");
    calcularTiempos(fib2, sqrt(log(2)), log(2), pow(2, 0.5));

    // Imprimir tabla para fib3
    printf("\nTiempos para fib3 (algoritmo de multiplicación de matrices)\n");
    calcularTiempos(fib3, sqrt(log(2)), log(2), pow(2, 0.5));

    return 0;
}
