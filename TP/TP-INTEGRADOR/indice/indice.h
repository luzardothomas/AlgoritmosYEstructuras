#ifndef INDICE_H_INCLUDED
#define INDICE_H_INCLUDED
#include "../lista/lista.h"
#define RUTA_INVALIDA   0
#define INACTIVO        0
#define POCOS_SOCIOS    0
#define INDICE_LLENO    0
#define INDICE_VACIO    0
#define DUPLICADO       0
#define SIN_MEM         0
#define NO_EXISTE        0
#define NO_ENCONTRADO   0
#define ENCONTRADO      1
#define TODO_OK         1
#define MEN(x,y) ((x) < (y) ? (x) : (y))
typedef int (*cmp)(const void*, const void*);
typedef void (*accion)(const void *, unsigned, void *);
typedef struct{
  tLista lista;
  size_t tamClave;
  cmp comp;
  void* regInd;
}
tIndice;

///Primitivas TDA Índice

void crearIndice(tIndice* ind, size_t tamClave, cmp comp);
int insertarIndice(tIndice* pin, void *clave, unsigned nroReg);
int eliminarIndice(tIndice* pin, void *clave,unsigned* nroReg);
int buscarIndice(const tIndice* pin, void *clave, unsigned* nroReg);
int cargarIndice(tIndice* pin, const char* path);
int grabarIndice(const tIndice* pin, const char* path);
void vaciarIndice(tIndice* pin);
int recorrerIndice(const tIndice* pin, accion act, void* param);

#endif // INDICE_H_INCLUDED
