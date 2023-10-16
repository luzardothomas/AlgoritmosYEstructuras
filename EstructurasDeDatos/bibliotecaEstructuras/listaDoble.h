#ifndef LISTADOBLE_H_INCLUDED
#define LISTADOBLE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define minimo(x,y) ((x) < (y) ? (x) : (y))

#define OK 1
#define DUPLICADO 2

typedef struct sNodo{
  void* dato;
  size_t tam;
  struct sNodo* ant, *sig;
}tNodo;

typedef tNodo* tLista;

void crearLista(tLista* pl);
void vaciarLista(tLista* pl);
int listaVacia(const tLista* pl);
int listaLlena(const tLista* pl, size_t tam);
int ponerAlComienzo(tLista* pl, const void* dato, size_t tam);
int ponerAlFinal(tLista* pl, const void* dato, size_t tam);
int mostrarDeDerechaAIzquierda(tLista* pl, void(*mostrar)(const void*));
int mostrarDeIzquierdaADerecha(tLista* pl, void(*mostrar)(const void*));
int ponerEnOrden(tLista* pl, const void* dato, size_t tam, int (*cmp)(const void*,const void*));
tLista* buscarMenor(tLista* pl,int (*cmp)(const void*,const void*));
void ordenarLista(tLista* pl,int (*cmp)(const void*,const void*));
tLista* buscarOcurrencia(tLista* pl, int (*cmp)(const void*,const void*));
int agrupar(tLista* pl,int (*cmp)(const void*,const void*),int (*acum)(void*,const void*));
int eliminarPorClave(tLista* pl, const void* comp,int (*cmp)(const void*,const void*));
int filter(tLista* pl,const void* comp,int (*cmp)(const void*,const void*));
int reduce(tLista* pl,void* acum,int (*facum)(void*,const void*));

int sacarPrimero(tLista* pl,void* dato, size_t tam); /// No existe
int sacarUltimo(tLista* pl,void* dato, size_t tam); /// No existe

#endif // LISTADOBLE_H_INCLUDED
