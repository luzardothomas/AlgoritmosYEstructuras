#ifndef PILAEST_H_INCLUDED
#define PILAEST_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_PILA 500
#define MENOR(X,Y) ((X) <= (Y)? (X): (Y))
typedef struct{
  char pila[TAM_PILA];
  size_t tope;
}tPila;

void crearPila(tPila* pp);
int apilar(tPila* pp, const void* dato, size_t tam);
int desapilar(tPila* pp, void* dato, size_t tam);
void vaciarPila(tPila* pp);
int verTope(const tPila* pp, void* dato, size_t tam);
int pilaVacia(const tPila* pp);
int pilaLlena(const tPila *p,size_t tam);


#endif // PILAEST_H_INCLUDED
