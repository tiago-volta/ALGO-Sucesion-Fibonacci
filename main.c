#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <sys/time.h>

//Cabeceras de las funciones
int fib1(int n);
int fib2(int n);
int fib3(int n);
void test();
double microsegundos();
void imprimirTiempos(int(*func)(int),int *valores, int tipo, int repeticiones);
void imprimirTablas();
double cotaAjustada(int n, int tipo);
double medirTiempo(int (*func)(int), const int n, bool *promedio, int k);
double cotaSubestimada(int n, int tipo);
double cotaSobreestimada(int n, int tipo);

//Realiza las pruebas de los algoritmos y muestra las tablas de tiempos
int main(void) {
    test();
    imprimirTablas();
    return 0;
}

//Implementación del algoritmo Fibonacci 1: recursivo
int fib1(int n) {
    if (n < 2)
        return n;
    return fib1(n - 1) + fib1(n - 2);
}

//Implementación del algoritmo Fibonacci 2: iterativo
int fib2(int n) {
    int i = 1, j = 0;
    for (int k = 1; k <= n; k++) {                                                //Error: No definir la variable en el bucle for, todas las variables de una función se definen al principio
        j = i + j; //Calcula el siguiente número de Fibonacci
        i = j - i; //Actualiza i para la siguiente iteración
    }
    return j;
}

//Implementación del algoritmo Fibonacci 3: multiplicación de matrices
int fib3(int n) {
    int i = 1, j = 0, k = 0, h = 1, t;
    while (n > 0) {
        if ((n % 2) != 0) { //Si n es impar
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

//Función para probar los tres algoritmos de Fibonacci
void test() {
    printf("\n%21s\n\n", "Test Fibonacci");
    printf("%2s%10s%8s%8s\n", "n", "fib1", "fib2", "fib3");
    printf("%s%8s%8s%8s\n", "----", "----", "----", "----");
    for (int i = 1; i <= 20; i++) {                                                        //Error: No definir la variable en el bucle for, todas las variables de una función se definen al principio
        printf("%-8d%d%8d%8d\n", i, fib1(i), fib2(i), fib3(i));
    }
}

//Obtiene la hora actual en microsegundos
double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0)
        return 0.0; //Maneja el error en la obtención del tiempo
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

//Mide el tiempo de ejecución
double medirTiempo(int (*func)(int), const int n, bool *promedio, int k) {
    double t1, t2, t;
    t1 = microsegundos();
    func(n);
    t2 = microsegundos();
    t = t2 - t1;

    //Si el tiempo es menor que 500 microsegundos
    if (t < 500) {
        t1 = microsegundos();
        for (int j = 0; j < k; j++)                                                    //Error: No definir la variable en el bucle for, todas las variables de una función se definen al principio
            func(n); //Llama a la función varias veces
        t2 = microsegundos();
        t = (t2 - t1) / k;
        *promedio = true; //Indica que se realizó un promedio
    }
    return t;
}

//Devuelve la cota subestimada para el algoritmo correspondiente
double cotaSubestimada(int n, int tipo) {
    switch (tipo) {
        case 1: //Para fib1
            return pow(1.1, n);
        case 2: //Para fib2
            return pow(n, 0.8);
        case 3: //Para fib3
            return sqrt(log(n));
        default:
            return 1.0; //Valor por defecto
    }
}

//Devuelve la cota ajustada para el algoritmo correspondiente
double cotaAjustada(int n, int tipo) {
    switch (tipo) {
        case 1: // Para fib1
            return pow((1 + sqrt(5)) / 2, n);
        case 2: // Para fib2
            return n;
        case 3: // Para fib3
            return log(n);
        default:
            return 1.0; //Valor por defecto
    }
}

//Devuelve la cota sobreestimada para el algoritmo correspondiente
double cotaSobreestimada(int n, int tipo) {
    switch (tipo) {
        case 1: //Para fib1
            return pow(2, n);
        case 2: //Para fib2
            return n * log(n);
        case 3: //Para fib3
            return pow(n, 0.5);
        default:
            return 1.0; //Valor por defecto
    }
}

//Imprime los tiempos de ejecución de la función dada
void imprimirTiempos(int(*func)(int),int* valores, int tipo, int repeticiones){
    double t, x, y, z;
    for (int i = 0; i < 5; i++) {                                                                //Error: No definir la variable en el bucle for, todas las variables de una función se definen al principio
        bool promedio = false; //Indica si se calculó un promedio                                //Error: No definir las varibles al principio de la función, además, las definimos dentro del bucle son ineficientes
        int n = valores[i];                                                                      //Error: No definir las varibles al principio de la función, además, las definimos dentro del bucle son ineficientes
        t = medirTiempo(func, n, &promedio, repeticiones);
        x = t / cotaSubestimada(n, tipo);
        y = t / cotaAjustada(n, tipo);
        z = t / cotaSobreestimada(n, tipo);

        if (promedio) {
            printf("*"); //Marca si se hizo un promedio
        } else {
            printf(" "); //Para mantener la alineación en la tabla
        }
        printf("%12d%17.4f%18.6f%18.6f%20.8f\n", n, t, x, y, z);
    }
}

//Imprime las tablas de tiempos para los diferentes algoritmos de Fibonacci
void imprimirTablas() {
    //Valores para el algoritmo 1
    int valoresFib1[5] = {2, 4, 8, 16, 32};
    //Valores para los algoritmos 2 y 3
    int valoresFib2Fib3[5] = {1000, 10000, 100000, 1000000, 10000000};
    printf("\n%55s\n\n", "Tablas de tiempos Fibonacci");

    //Fibonacci 1
    printf("\nAlgoritmo fibonacci 1\n");
    printf("\n%13s%16s%20s%25s%11s\n",
        "n", "t(n)", "t(n)/1.1^n", "t(n)/((1+sqrt(5))/2)^n", "t(n)/2^n");
    imprimirTiempos(fib1, valoresFib1, 1, 100000);

    //Fibonacci 2
    printf("\nAlgoritmo fibonacci 2\n");
    printf("\n%12s%17s%20s%16s%22s\n",
        "n", "t(n)", "t(n)/n^0.8", "t(n)/n", "t(n)/n*log(n)");
    imprimirTiempos(fib2, valoresFib2Fib3, 2, 1000);

    //Fibonacci 3
    printf("\nAlgoritmo fibonacci 3\n");
    printf("\n%12s%17s%23s%16s%18s\n",
        "n", "t(n)", "t(n)/sqrt(log(n))", "t(n)/log(n)", "t(n)/n^0,5");
    imprimirTiempos(fib3, valoresFib2Fib3 ,3,10000);
}



/ Función que verifica si un arreglo está ordenado de manera ascendente
bool ordenado_ascendente(int arr[], int tam) {
    for (int i = 0; i < tam - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

// Función que verifica si un arreglo está ordenado de manera descendente
bool ordenado_descendente(int arr[], int tam) {
    for (int i = 0; i < tam - 1; i++) {
        if (arr[i] < arr[i + 1]) {
            return false;
        }
    }
    return true;
}

// Función que verifica si un arreglo está ordenado de cualquier manera
int ordenado(int arr[], int tam) {
    if (ordenado_ascendente(arr, tam)) {
        return 1;
    } else if (ordenado_descendente(arr, tam)) {
        return -1;
    } else {
        return 0;
    }
}






#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// Función que verifica si un arreglo está ordenado de manera ascendente
bool ordenado_ascendente(int arr[], int tam) {
    for (int i = 0; i < tam - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

// Función que verifica si un arreglo está ordenado de manera descendente
bool ordenado_descendente(int arr[], int tam) {
    for (int i = 0; i < tam - 1; i++) {
        if (arr[i] < arr[i + 1]) {
            return false;
        }
    }
    return true;
}

// Función que verifica si un arreglo está ordenado de cualquier manera
int ordenado(int arr[], int tam) {
    if (ordenado_ascendente(arr, tam)) {
        return 1;
    } else if (ordenado_descendente(arr, tam)) {
        return -1;
    } else {
        return 0;
    }
}







// Función para inicializar un arreglo con valores aleatorios
void inicializar_aleatorio(int arr[], int tam) {
    srand(time(NULL));
    for (int i = 0; i < tam; i++) {
        arr[i] = rand() % 31 - 15; // Valores aleatorios entre -15 y 15
    }
}

// Función para inicializar un arreglo con valores descendentes
void inicializar_descendente(int arr[], int tam) {
    for (int i = 0; i < tam; i++) {
        arr[i] = tam - i;
    }
}

int main(void) {
    int arr1[] = {3, -3, 0, 17, -5, 2, 11, 13, 6, 1, 7, 14, 1, -2, 5, -14, -2};
    int tam1 = sizeof(arr1) / sizeof(arr1[0]);

    printf("Ordenación por inserción con inicialización aleatoria\n");
    imprimir_arreglo(arr1, tam1);
    printf("ordenado? %d\n", ordenado(arr1, tam1));
    printf("ordenando...\n");
    imprimir_arreglo(arr1, tam1);
    printf("ordenado? %d\n", ordenado(arr1, tam1));

    int tam2 = 10;
    int arr2[tam2];
    inicializar_descendente(arr2, tam2);

    printf("Ordenación por inserción con inicialización descendente\n");
    imprimir_arreglo(arr2, tam2);
    printf("ordenado? %d\n", ordenado(arr2, tam2));
    printf("ordenando...\n");
    imprimir_arreglo(arr2, tam2);
    printf("ordenado? %d\n", ordenado(arr2, tam2));

    int arr3[] = {3, -3, 0, 17, -5, 2, 11, 13, 6, 1, 7, 14, 1, -2, 5, -14, -2};
    int tam3 = sizeof(arr3) / sizeof(arr3[0]);

    printf("Ordenación rápida con inicialización aleatoria\n");
    imprimir_arreglo(arr3, tam3);
    printf("ordenado? %d\n", ordenado(arr3, tam3));
    printf("ordenando...\n");
    imprimir_arreglo(arr3, tam3);
    printf("ordenado? %d\n", ordenado(arr3, tam3));

    int arr4[tam2];
    inicializar_descendente(arr4, tam2);

    printf("Ordenación rápida con inicialización descendente\n");
    imprimir_arreglo(arr4, tam2);
    printf("ordenado? %d\n", ordenado(arr4, tam2));
    printf("ordenando...\n");
    imprimir_arreglo(arr4, tam2);
    printf("ordenado? %d\n", ordenado(arr4, tam2));

    return 0;
}



