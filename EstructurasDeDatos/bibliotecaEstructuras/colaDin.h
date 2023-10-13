#ifndef COLADIN_H_INCLUDED
#define COLADIN_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MENOR(X,Y) ((X) <= (Y)? (X):(Y))

typedef struct sNodo{
  void* dato;
  size_t tam;
  struct sNodo* sig;
}tNodo;

typedef struct{
  tNodo* ini;
  tNodo* fin;
}tCola;

void crearCola(tCola* pc);
int acolar(tCola* pc, const void* dato, size_t tam);
int desacolar(tCola* pc, void* dato, size_t tam);
int colaVacia(const tCola* pc);
void vaciarCola(tCola *pc);
int verPrimeroCola(tCola *pc,void* dato,size_t tam);
int colaLlena(const tCola* pc,size_t tam);





#endif // COLADIN_H_INCLUDED
