#ifndef COLAEST_H_INCLUDED
#define COLAEST_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_COLA 1000
#define ES_LETRA(X) (((X) >= 'A' && (X) <= 'Z') || ((X) >= 'a' && (X) <= 'z'))
#define MENOR(X,Y) ((X) < (Y)?(X):(Y))
#define minimo(x,y) ((x) < (y)?(x):(y))


typedef struct{
  char cola[TAM_COLA];
  size_t ini,fin,tamDisp;
}t_cola;

void crear_cola(t_cola *pc);
void vaciar_cola(t_cola* pc);
int a_colar(t_cola *pc, const void *dato, size_t tam);
int des_acolar(t_cola *pc, void *dato, size_t tam);
int cola_vacia(const t_cola *pc);
int cola_llena(const t_cola *pc, size_t tam);
int ver_primero_cola(const t_cola *pc, void *dato, size_t tam);


int acolar_(t_cola *pc, const void *dato, size_t tam);
int desacolar_(t_cola *pc, void *dato, size_t tam);

int acolar__(t_cola *pc, const void *dato, size_t tam);
int desacolar__(t_cola *pc, void *dato, size_t tam);

#endif // COLAEST_H_INCLUDED
