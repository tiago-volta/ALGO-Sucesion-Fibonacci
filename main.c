#include <stdio.h>
#include <math.h>
#include <sys/time.h>

//Obtiene la hora actual en microsegundos
double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0)
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

//Algoritmo fib1
int fib1(int n) {
    if (n < 2) return n;
    return fib1(n - 1) + fib1(n - 2);
}

//Algoritmo fib2
int fib2(int n) {
    int i = 1, j = 0;
    for (int k = 1; k <= n; k++) {
        int temp = i;
        i = i + j;
        j = temp;
    }
    return j;
}

//Algoritmo fib3
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

    //Medición para fib1
    printf("\nMediciones para fib1:\n");
    printf("%8s%22s%22s%22s\n", "n", "t(n)", "t(n)/sqrt(log(n))", "t(n)/log(n)");
    int n_values_fib1[] = {2, 4, 8, 16, 32};
    for (int i = 0; i < 5; i++) {
        n = n_values_fib1[i];
        t1 = microsegundos();
        fib1(n);
        t2 = microsegundos();
        t = t2 - t1;
        x = t / pow(1.1, n);
        y = t / pow(2, n);
        printf("%8d%22.3f%22.6f%22.6f\n", n, t, x, y);
    }

    //Medición para fib2
    printf("\nMediciones para fib2:\n");
    printf("%8s%22s%22s%22s\n", "n", "t(n)", "t(n)/sqrt(log(n))", "t(n)/log(n)");
    int n_valores_fib2[] = {1000, 10000, 100000, 1000000, 10000000};
    for (int i = 0; i < 5; i++) {
        n = n_valores_fib2[i];
        t1 = microsegundos();
        fib2(n);
        t2 = microsegundos();
        t = t2 - t1;
        x = t / pow(n, 0.8);
        y = t / (n * log(n));
        printf("%8d%22.3f%22.6f%22.6f\n", n, t, x, y);
    }

    //Medición para fib3
    printf("\nMediciones  para fib3:\n");
    printf("%8s%22s%22s%22s\n", "n", "t(n)", "t(n)/sqrt(log(n))", "t(n)/log(n)");
    int n_valores_fib3[] = {1000, 10000, 100000, 1000000, 10000000};
    for (int i = 0; i < 5; i++) {
        n = n_valores_fib3[i];
        t1 = microsegundos();
        fib3(n);
        t2 = microsegundos();
        t = t2 - t1;
        x = t / log(n);
        y = t / sqrt(n);
        printf("%8d%22.3f%22.6f%22.6f\n", n, t, x, y);
    }

    return 0;
}





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
    int i, max_prints = 3;
    int valores_n_fib1[] = {2, 4, 8, 16, 32};  
    int valores_n_fib2_y_fib3[] = {1000, 10000, 100000, 1000000, 10000000};  

    // Tabla para fib1 (recursivo)
    printf(" (fib1)\n");
    for (i = 0; i < max_prints; i++) {
        printf("\n%8s%15s%19s%15s%16s\n", "n", "t(n)", "t(n)/n^1.8", "t(n)/n^2", "t(n)/n^2.2");
        tTiempos(fib1, 1.8, 2, 2.2, valores_n_fib1, 5);
    }

    // Tabla para fib2 (iterativo)
    printf(" (fib2)\n");
    for (i = 0; i < max_prints; i++) {
        printf("\n%8s%15s%19s%15s%16s\n", "n", "t(n)", "t(n)/n^0.8", "t(n)/n^1", "t(n)/n^1.2");
        tTiempos(fib2, 0.8, 1, 1.2, valores_n_fib2_y_fib3, 5);
    }

    // Tabla para fib3 (multiplicación de matrices)
    printf(" (fib3)\n");
    for (i = 0; i < max_prints; i++) {
        printf("\n%8s%15s%19s%15s%16s\n", "n", "t(n)", "t(n)/n^0.5", "t(n)/n^0.7", "t(n)/n^0.9");
        tTiempos(fib3, 0.5, 0.7, 0.9, valores_n_fib2_y_fib3, 5);
    }
}

int main() {
    printTiempos();
    return 0;
}









#include <stdio.h>
#include <math.h>
#include <sys/time.h>

int fib1(int n);
int fib2(int n);
int fib3(int n);
void test();
double microsegundos();
void imprimirTiempos(int (*func)(int), int ninicial,int nfinal, int incremento);
void imprimirTablas();

//gcc -Wall main.c -o P1 -lm
//Poner la funcion test entre comentarios
int main(void) {
    imprimirTablas();
    return 0;
}

int fib1(int n) {
    if (n < 2)
        return n;
    return fib1(n-1) + fib1(n-2);
}

int fib2(int n) {
    int i = 1, j = 0;
    for (int k = 1; k <= n; k++) {
        j = i +j;
        i = j-i;
    }
    return j;
}
int fib3(int n) {
    int i = 1, j = 0, k = 0, h = 1, t;
    while ( n > 0 ) {
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

void test() {
    printf("\n%21s\n\n","Test Fibonacci");
    printf("%2s%10s%8s%8s\n","n","fib1","fib2","fib3");
    printf("%s%8s%8s%8s\n","----","----","----","----");
    for(int i = 1; i <= 20; i++) {
        printf("%-8d%d%8d%8d\n",i,fib1(i),fib2(i),fib3(i));
    }
}

/* obtiene la hora actual en microsegundos */
double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0)
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void imprimirTiempos(int (*func)(int), int ninicial,int nfinal, int incremento) {
    //N es el término de la sucesión de fibonacci a hallar
    double t1, t2, t, x, y, z;
    for (int n = ninicial; n <= nfinal; n = n*incremento) {
        t1 = microsegundos();
        func(n);
        t2 = microsegundos();
        t = t2-t1;
        x = t / sqrt(log(n));   //Comparación con la cota superior
        y = t / log(n);     //Comparacion con la cota superior
        z = t / pow(n, 0.5);    //Comparacion con la cota superior
        printf("%12d%15.3f%15.6f%15.6f%15.6f\n", n, t, x, y, z);
    }
}


void imprimirTablas() {
    printf("\n%55s\n\n", "Tablas de tiempos Fibonacci");

    // Fibonacci 1
    printf("\nAlgoritmo fibonacci 1\n");
    printf("\n%12s%15s%19s%14s%15s\n", "n", "t(n)", "t(n)/sqrt(log(n))", "t(n)/log(n)", "t(n)/sqrt(n)");
    imprimirTiempos(fib1, 2, 32, 2);   // Pequeños valores para fib1 ya que es recursivo

    // Fibonacci 2
    printf("\nAlgoritmo fibonacci 2\n");
    printf("\n%12s%15s%19s%14s%15s\n", "n", "t(n)", "t(n)/sqrt(log(n))", "t(n)/log(n)", "t(n)/sqrt(n)");
    imprimirTiempos(fib2, 1000, 10000000, 10); // Mayor rango para fib2 ya que es iterativo

    // Fibonacci 3
    printf("\nAlgoritmo fibonacci 3\n");
    printf("\n%12s%15s%19s%14s%15s\n", "n", "t(n)", "t(n)/sqrt(log(n))", "t(n)/log(n)", "t(n)/n^0,5");
    imprimirTiempos(fib3, 1000, 10000000, 10); // Mayor rango para fib3 ya que es optimizado
}




