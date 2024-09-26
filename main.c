#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <sys/time.h>

int fib1(int n);
int fib2(int n);
int fib3(int n);
void test();
double microsegundos();
void imprimirTiempos(int (*func)(int), const int * valores, const int tipo,const int repeticiones);
void imprimirTablas();
double cotaAjustada(int n, int tipo);
double medirTiempo(int (*func)(int),const int n,bool *promedio,int k);
double cotaSubestimada(int n, int tipo);
double cotaSobreestimada(int n, int tipo);

//gcc -Wall main.c -o P1 -lm
//Poner la funcion test entre comentarios
int main(void) {
    test();
    imprimirTablas();
    imprimirTablas();
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

double medirTiempo(int (*func)(int),const int n,bool *promedio,int k){
    double t1, t2, t;
    t1 = microsegundos();
    func(n);
    t2 = microsegundos();
    t = t2-t1;
    if (t<500) {        //Si el tiempo es muy pequeño hacemos más repeticiones y hacemos una media
        t1 = microsegundos();
        for (int j = 0; j < k; j++)
            func(n);
        t2 = microsegundos();
        t = (t2 - t1) / k;
        *promedio = true;
    }
    return t;
}

double cotaSubestimada(int n, int tipo) {
    switch (tipo) {
        case 1: // Para fib1
            return pow(1.1,n);
        case 2: // Para fib2
            return pow(n, 0.8);
        case 3: // Para fib3
            return sqrt(log(n));
        default:
            return 1.0;
    }
}

double cotaAjustada(int n, int tipo) {
    switch (tipo) {
        case 1: // Para fib1
            return pow((1 + sqrt(5)) / 2, n);
        case 2: // Para fib2
            return n;
        case 3: // Para fib3
            return log(n);
        default:
            return 1.0;
    }
}

double cotaSobreestimada(int n, int tipo) {
    switch (tipo) {
        case 1: // Para fib1
            return pow(2, n);
        case 2: // Para fib2
            return n*log(n);
        case 3: // Para fib3
            return pow(n, 0.5);
        default:
            return 1.0;
    }
}

void imprimirTiempos(int (*func)(int), const int * valores, const int tipo,const int repeticiones) {
    //N es el término de la sucesión de fibonacci a hallar
    double t, x, y, z;
    for (int i = 0; i < 5; i++) {
        bool promedio = false;
        int n = valores[i];
        t = medirTiempo(func,n,&promedio,repeticiones);
        x = t / cotaSubestimada(n,tipo);   //Comparación con la cota subestimada
        y = t / cotaAjustada(n,tipo);     //Comparacion con la cota ajustada
        z = t / cotaSobreestimada(n,tipo);    //Comparacion con la cota sobreestimada
        if (promedio) {
            printf("*");
        }else {
            printf(" ");
        }
        printf("%12d%17.4f%18.6f%18.6f%20.8f\n", n, t, x, y, z);
    }
}



void imprimirTablas() {
    int valoresFib1[5] = {2,4,8,16,32};
    int valoresFib2Fib3[5] = {1000,10000,100000,1000000,10000000};
    printf("\n%55s\n\n", "Tablas de tiempos Fibonacci");

    // Fibonacci 1
    printf("\nAlgoritmo fibonacci 1\n");
    printf("\n%13s%16s%20s%25s%11s\n", "n", "t(n)", "t(n)/1.1^n", "t(n)/((1+sqrt(5))/2)^n", "t(n)/2^n");
    imprimirTiempos(fib1, valoresFib1,1,100000);   // Pequeños valores para fib1 ya que es recursivo
    //tiemposFib1();

    // Fibonacci 2
    printf("\nAlgoritmo fibonacci 2\n");
    printf("\n%12s%17s%20s%16s%22s\n", "n", "t(n)", "t(n)/n^0.8", "t(n)/n", "t(n)/n*log(n)");
    imprimirTiempos(fib2, valoresFib2Fib3,2,1000); // Mayor rango para fib2 ya que es iterativo
    //tiemposFib2();

    // Fibonacci 3
    printf("\nAlgoritmo fibonacci 3\n");
    printf("\n%12s%17s%23s%16s%18s\n", "n", "t(n)", "t(n)/sqrt(log(n))", "t(n)/log(n)", "t(n)/n^0,5");
    imprimirTiempos(fib3, valoresFib2Fib3 ,3,10000); // Mayor rango para fib3 ya que es optimizado
    //tiemposFib3();
}



