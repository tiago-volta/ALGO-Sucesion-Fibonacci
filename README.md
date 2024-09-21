# ALGO-Sucesion-Fibonacci
# Práctica 1 - Algoritmos de Fibonacci

Este repositorio contiene la implementación de tres algoritmos diferentes para calcular la sucesión de Fibonacci, como parte de la Práctica 1 del curso de **Algoritmos**. El objetivo es analizar empíricamente la eficiencia de estos algoritmos y comparar sus tiempos de ejecución.



## Objetivo

La práctica tiene como objetivo:
1. Implementar tres algoritmos para calcular la sucesión de Fibonacci:
   - **Algoritmo fib1**: Recursivo, con complejidad O(φ^n), donde φ = (1 + √5) / 2.
   - **Algoritmo fib2**: Iterativo, con complejidad O(n).
   - **Algoritmo fib3**: Basado en matrices, con complejidad O(log n).
2. Validar el correcto funcionamiento de los algoritmos.
3. Comparar los tiempos de ejecución para distintos tamaños de entrada.
4. Analizar los resultados obtenidos y compararlos con las cotas teóricas propuestas.



## Implementación

### Algoritmo fib1

Implementación recursiva de la sucesión de Fibonacci. Aunque es intuitiva, es menos eficiente para valores grandes de `n` debido a su alta complejidad.

### Algoritmo fib2

Implementación iterativa que mejora el rendimiento con una complejidad lineal O(n). Es más eficiente para entradas grandes en comparación con el algoritmo recursivo.

### Algoritmo fib3

Uso de técnicas de multiplicación de matrices para calcular el valor de Fibonacci con una complejidad logarítmica O(log n). Adecuado para valores de `n` muy grandes.
