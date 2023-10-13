#ifndef PILACIRCULAR_H_INCLUDED
#define PILACIRCULAR_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define minimo(x,y) ((x) < (y) ? (x) : (y))
typedef struct sNodo{
  void* dato;
  size_t tam;
  struct sNodo* sig;
}tNodo;

typedef tNodo* tPilaC;

void crearPila(tPilaC* pc);
int apilar(tPilaC* pc, const void* dato, size_t tam);
int desapilar(tPilaC* pc,void* dato, size_t tam);
void vaciarPila(tPilaC* pc);
int pilaVacia(const tPilaC* pc);
int pilaLlena(const tPilaC* pc, size_t tam);
int verTope(const tPilaC* pc,void* dato ,size_t tam);
#endif // PILACIRCULAR_H_INCLUDED
