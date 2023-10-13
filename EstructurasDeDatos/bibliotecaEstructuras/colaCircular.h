#ifndef COLACIRCULAR_H_INCLUDED
#define COLACIRCULAR_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define minimo(x,y) ((x) < (y) ? (x) : (y))
typedef struct sNodo{
  void* dato;
  size_t tam;
  struct sNodo* sig;
}tNodo;

typedef tNodo* tColaC;

void crearCola(tColaC* cc);
void vaciarCola(tColaC* cc);
int acolar(tColaC* cc, const void* dato, size_t tam);
int desacolar(tColaC* cc,void* dato, size_t tam);
int colaLlena(const tColaC* cc,size_t tam);
int colaVacia(const tColaC* cc);
int verPrimero(tColaC* cc, void* dato, size_t tam);

#endif // COLACIRCULAR_H_INCLUDED
