#ifndef PILADIN_H_INCLUDED
#define PILADIN_H_INCLUDED
#define MIN(X,Y) ((X) <= (Y)? (X):(Y))
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct sNodo{
  void* dato;
  size_t tam;
  struct sNodo* sig;
}tNodo;

typedef tNodo* tPila;

void crearPila(tPila* pp);
int apilar(tPila* pp, const void* dato, size_t tam);
int desapilar(tPila* pp, void* dato, size_t tam);
void vaciarPila(tPila* pp);
int verTope(const tPila* pp, void* dato, size_t tam);
int pilaVacia(const tPila* pp);
int pilaLlena(const tPila *p,size_t tam);

#endif // PILADIN_H_INCLUDED
