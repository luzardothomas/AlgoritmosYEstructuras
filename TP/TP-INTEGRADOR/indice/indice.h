#ifndef INDICE_H_INCLUDED
#define INDICE_H_INCLUDED

#include <stdlib.h>

#define INDICE_LLENO    0
#define INDICE_VACIAO   0
#define DUPLICADO       0
#define SIN_MEM       0
#define TODO_OK         1

#define MEN(x,y) ((x) < (y) ? (x) : (y))

#include "../TP.h"

typedef struct sNodoInd{

  void *dato;
  unsigned tam;
  struct sNodoI *sig;

}tNodoInd;

typedef tNodoInd* tIndice;


typedef int (*cmp)(const void*, const void*);
typedef void (*accion)(const void *, unsigned, void *);

void crearIndice(tIndice* pin);
int insertarIndice(tIndice* pin, void *clave, unsigned nroReg);
int eliminarIndice(tIndice* pin, void *clave, unsigned nroReg,cmp comp);
int buscarIndice(const tIndice* pin, void *clave, unsigned nroReg);
int cargarIndice(tIndice* pin, const char* path);
int grabarIndice(const tIndice* pin, const char* path);
void vaciarIndice(tIndice* pin);
int recorrerIndice(const tIndice* pin,accion act , void* param);


#endif // INDICE_H_INCLUDED
