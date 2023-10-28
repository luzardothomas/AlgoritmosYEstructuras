#ifndef INDICE_H_INCLUDED
#define INDICE_H_INCLUDED

#include <stdlib.h>

#define INDICE_LLENO    0
#define INDICE_VACIAO   0
#define DUPLICADO       0
#define TODO_OK         1

#define MEN(x,y) ((x) < (y) ? (x) : (y))

typedef struct sNodoI
{
    void *info;
    size_t tam;
    struct sNodoI *sig;
} tNodoI;

typedef tNodoI* tIndice;


typedef int (*Cmp)(const void*, const void*);
typedef void (*Accion2)(const void *, unsigned, void *);

void indCrear(tIndice* ind, size_t tam,Cmp cmp);
int indInsertar (tIndice* ind, void *clave, unsigned nro);
int indEliminar (tIndice* ind, void *clave, unsigned nro);
int indBuscar (const tIndice* ind, void *clave, unsigned nro);
int indCargar (tIndice* ind, const char* path);
int indGrabar (const tIndice* ind, const char* path);
void indVaciar (tIndice* ind);
int indRecorrer (const tIndice* ind,Accion2 accion , void* param);


#endif // INDICE_H_INCLUDED
