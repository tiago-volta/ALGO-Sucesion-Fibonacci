#include <stdio.h>
#include <math.h>
#include <sys/time.h>

// Obtiene la hora actual en microsegundos
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
    int i = 1, j = 0;
    for (int k = 1; k <= n; k++) {
        int temp = i;
        i = i + j;
        j = temp;
    }
    return j;
}

// Algoritmo fib3
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

int main() {
    int n;
    double t1, t2, t, x, y;
    int k = 1000;  // Número de repetições

    // Medición para fib1
    printf("\nMediciones para fib1:\n");
    printf("%8s%22s%22s%22s\n", "n", "t(n)", "t(n)/sqrt(log(n))", "t(n)/log(n)");
    int n_values_fib1[] = {2, 4, 8, 16, 32};
    for (int i = 0; i < 5; i++) {
        n = n_values_fib1[i];
        t1 = microsegundos();
        fib1(n);
        t2 = microsegundos();
        t = t2 - t1;

        //Verifica si el tiempo es menor de 500 microsegundos
        if (t < 500) {
            t1 = microsegundos();
            for (int j = 0; j < k; j++) {
                fib1(n);
            }
            t2 = microsegundos();
            t = (t2 - t1) / k;  // Tempo médio
        }

        x = t / pow(1.1, n);
        y = t / pow(2, n);
        printf("%8d%22.3f%22.6f%22.6f\n", n, t, x, y);
    }

    // Medición para fib2
    printf("\nMediciones para fib2:\n");
    printf("%8s%22s%22s%22s\n", "n", "t(n)", "t(n)/sqrt(log(n))", "t(n)/log(n)");
    int n_valores_fib2[] = {1000, 10000, 100000, 1000000, 10000000};
    for (int i = 0; i < 5; i++) {
        n = n_valores_fib2[i];
        t1 = microsegundos();
        fib2(n);
        t2 = microsegundos();
        t = t2 - t1;

        //Verifica si el tiempo es menor de 500 microsegundos
        if (t < 500) {
            t1 = microsegundos();
            for (int j = 0; j < k; j++) {
                fib2(n);  
            }
            t2 = microsegundos();
            t = (t2 - t1) / k;  // Tempo médio
        }

        x = t / pow(n, 0.8);
        y = t / (n * log(n));
        printf("%8d%22.3f%22.6f%22.6f\n", n, t, x, y);
    }

    // Medición para fib3
    printf("\nMediciones para fib3:\n");
    printf("%8s%22s%22s%22s\n", "n", "t(n)", "t(n)/sqrt(log(n))", "t(n)/log(n)");
    int n_valores_fib3[] = {1000, 10000, 100000, 1000000, 10000000};
    for (int i = 0; i < 5; i++) {
        n = n_valores_fib3[i];
        t1 = microsegundos();
        fib3(n);
        t2 = microsegundos();
        t = t2 - t1;

        //Verifica si el tiempo es menor de 500 microsegundos
        if (t < 500) {
            t1 = microsegundos();
            for (int j = 0; j < k; j++) {
                fib3(n);
            }
            t2 = microsegundos();
            t = (t2 - t1) / k;  // Tempo médio
        }

        x = t / log(n);
        y = t / sqrt(n);
        printf("%8d%22.3f%22.6f%22.6f\n", n, t, x, y);
    }

    return 0;
}

