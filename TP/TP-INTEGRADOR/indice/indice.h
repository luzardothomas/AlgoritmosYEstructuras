#ifndef INDICE_H_INCLUDED
#define INDICE_H_INCLUDED

#include "../TP.h"

#define INDICE_LLENO    0
#define INDICE_VACIO    0
#define DUPLICADO       0
#define SIN_MEM         0
#define TODO_OK         1

#define MEN(x,y) ((x) < (y) ? (x) : (y))


typedef int (*cmp)(const void*, const void*);
typedef void (*accion)(const void *, unsigned, void *);

typedef struct sigInd{
  void* clave;
  unsigned nroReg;
  struct sigInd* sig;
}indice;

typedef struct{
  tLista* lista;
  ///indice* ind;
  size_t tamClave;
  cmp comp;
  ///nroReg = 1

}tIndice;



void mostrarIndice(const tIndice* pin, void (*mostrar)(const void*,FILE*),FILE* pf);

void crearIndice(tIndice* ind, size_t tamClave, cmp comp);
int insertarIndice(tIndice* pin, void *clave, unsigned nroReg);
int eliminarIndice(tIndice* pin, void *clave, unsigned nroReg,cmp comp);
int buscarIndice(const tIndice* pin, void *clave, unsigned nroReg);
int cargarIndice(tIndice* pin, const char* path);
int grabarIndice(const tIndice* pin, const char* path);
void vaciarIndice(tIndice* pin);
int recorrerIndice(const tIndice* pin,accion act , void* param);


#endif // INDICE_H_INCLUDED
