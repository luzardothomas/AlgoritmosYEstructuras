#ifndef LISTASIMPLE_H_INCLUDED
#define LISTASIMPLE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define minimo(x,y) ((x)<(y) ? (x):(y))

typedef struct sNodo{
  void* dato;
  size_t tam;
  struct sNodo* sig;
}tNodo;

typedef tNodo* tLista;

void crearLista(tLista* pl);
int listaVacia(const tLista* pl);
int listaLlena(const tLista* pl, size_t tam);
void vaciarLista(tLista* pl);
int ponerAlComienzo(tLista* pl, const void* dato, size_t tam);
int sacarPrimeroLista(tLista* pl, void* dato, size_t tam);
int verPrimeroLista(const tLista* pl, void* dato, size_t tam);
int ponerAlFinal(tLista* pl, const void* dato, size_t tam);
int sacarUltimoLista(tLista* pl, void* dato, size_t tam);
int verUltimoLista(const tLista* pl, void* dato, size_t tam);
int mostrarLista(const tLista* pl, void (*mostrar) (const void*,FILE*),FILE* pf);
int mostrarListaAlReves(const tLista* pl, void (*mostrar)(const void*, FILE*), FILE* pf);
int mostrarListaYVaciar(tLista* pl, void (*mostrar)(const void*,FILE*),FILE* pf);
int mostrarListaAlRevesYVaciar(tLista* pl, void (*mostrar)(const void*,FILE*),FILE* pf);
int ponerEnOrden(tLista* pl,const void* dato, size_t tam,
                 int (*cmp)(const void*, const void*),
                 int(*acumular)(void**,size_t*,const void*,size_t));
int mostrarListaYVaciar(tLista* pl, void (*mostrar)(const void*,FILE*),FILE* pf);
void ordenar(tLista* pl, int(*cmp)(const void*,const void*));
tLista* buscarMenor(tLista* pl, int(*cmp)(const void*,const void*));
void ordenarLista(tLista* pl, int(*cmp)(const void*,const void*));

void reduceList(tLista* pl,void* acu, void (*acum)(void*,const void*));
int filterList(tLista* pl,void* comp, int (*cmp)(const void*,const void*));

tLista* buscarOcurrencia(const tLista* pl,const void* ocur,int(*cmp)(const void*,const void*));
int agrupar(tLista* pl, int(*cmp)(const void*,const void*), int (*acum)(void*,const void*));
int eliminarPorClave(tLista* pl,const void* dato,int(*cmp)(const void*,const void*));



#endif // LISTASIMPLE_H_INCLUDED
