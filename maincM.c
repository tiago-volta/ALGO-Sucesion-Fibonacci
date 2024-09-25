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

// Algoritmo fib1 (Recursivo)
int fib1(int n) {
    if (n < 2) return n;
    return fib1(n - 1) + fib1(n - 2);
}

// Algoritmo fib2 (Iterativo)
int fib2(int n) {
    int i = 1, j = 0;
    for (int k = 1; k <= n; k++) {
        int temp = i;
        i = i + j;
        j = temp;
    }
    return j;
}

// Algoritmo fib3 (Matrices)
int fib3(int n) {
    int i = 1, j = 0, k = 0, h = 1, t;
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

// Función que mide tiempos y genera las tablas de acuerdo a los exponentes
void medirTiempos(int (*funct)(int), double exp1, double exp2, double exp3, int* valores_n, int tam, const char* algoritmo) {
    double t0, t1, tf;
    int k = 1000;

    printf("\nMediciones para %s:\n", algoritmo);
    printf("%8s%15s%19s%15s%16s\n", "n", "t(n)", "t(n)/n^exp1", "t(n)/n^exp2", "t(n)/n^exp3");

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

// Función para imprimir las tablas de tiempos de los algoritmos
void printTiempos() {
    int valores_n_fib1[] = {2, 4, 8, 16, 32};
    int valores_n_fib2_y_fib3[] = {1000, 10000, 100000, 1000000, 10000000};

    // Tabla para fib1 (recursivo)
    medirTiempos(fib1, 1.8, 2, 2.2, valores_n_fib1, 5, "fib1 (recursivo)");

    // Tabla para fib2 (iterativo)
    medirTiempos(fib2, 0.8, 1, 1.2, valores_n_fib2_y_fib3, 5, "fib2 (iterativo)");

    // Tabla para fib3 (multiplicación de matrices)
    medirTiempos(fib3, 0.5, 0.7, 0.9, valores_n_fib2_y_fib3, 5, "fib3 (multiplicación de matrices)");
}

// Función opcional para verificar que los algoritmos producen el mismo resultado
void verificarResultados(int n) {
    int res1 = fib1(n);
    int res2 = fib2(n);
    int res3 = fib3(n);

    if (res1 == res2 && res2 == res3) {
        printf("Fibonacci(%d) = %d (verificado correctamente)\n", n, res1);
    } else {
        printf("Error: Fibonacci(%d) es inconsistente entre algoritmos (fib1: %d, fib2: %d, fib3: %d)\n", n, res1, res2, res3);
    }
}

int main() {
    // Validación opcional de resultados
    printf("Verificando que todos los algoritmos produzcan el mismo resultado para algunos valores...\n");
    verificarResultados(10);  // Cambia los valores si quieres verificar otros
    verificarResultados(20);
    verificarResultados(30);

    // Imprime los tiempos de ejecución
    printTiempos();

    return 0;
}
