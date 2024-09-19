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

int main() {
    int n;
    double t1, t2, t, x, y, z;
    n=8;
    t1 = microsegundos();
    fib1(n);
    t2 = microsegundos();
    t = t2-t1;
    x = t / sqrt(log(n));
    y = t / log(n);
    z = t / pow(n, 0.5);
    printf("%12d%15.3f%15.6f%15.6f%15.6f\n", n, t, x, y, z);
}

