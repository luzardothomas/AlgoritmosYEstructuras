#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MENOR(X,Y) (((X) < (Y)) ? (X) : (Y))
#define MAYOR(X,Y) (((X) > (Y)) ? (X) : (Y))
#define MOD(X) (((X) > 0) ? (X) : (-X))
#define ARBOL_VACIO 0
#define SIN_MEM     0
#define DUPLICADO   2
#define TODO_OK     1
typedef struct sNodoArbol{
  void* dato;
  size_t tam;
  struct sNodoArbol* der,*izq;
}tNodoArbol;

typedef tNodoArbol* tArbol;
typedef int (*cmp)(const void*,const void*);
typedef void (*accion)(void*,void*);

void crearArbol(tArbol* pa);
int insertarArbol(tArbol* pa, const void* dato, size_t tam,cmp comp);
int insertarArbolRecursivo(tArbol* pa, const void* dato, size_t tam,cmp comp);
void recorrerArbolEnOrden(const tArbol* pa, accion act, void* param);
void recorrerArbolPreOrden(const tArbol* pa, accion act, void* param);
void recorrerArbolPosOrden(const tArbol* pa, accion act, void* param);
void vaciarArbol(tArbol* pa);
void podarNivel(tArbol* pa, int n);
int contarNodos(tArbol* pa);
int alturaNivel(tArbol* pa);
int mayor(tArbol* pa,void* dato, size_t tam);
tArbol* mayorNodo(tArbol* pa);
tArbol* menorNodo(tArbol* pa);
int eliminarRaiz(tArbol* pa, void* dato,size_t tam);
///Para un vector
int cargarArbolOrdR(tArbol* pa, void* orig, size_t tam,int li, int ls);
///Genérico
int cargarDatosOrdR(tArbol* pa, void* orig, size_t tam,int li, int ls,
                    int (*copiarDatoOrig)(void* dest,void* orig,size_t tam, int pos));
int copiarDatoVec(void* dest,void* orig,size_t tam, int pos);
int copiarDatoArch(void* dest,void* orig,size_t tam, int pos);
int cargarArbolArch(tArbol* pa, char* path, size_t tam);
///Balanceo
int arbolCompletoHastaNivel(tArbol* pa, int n);
int arbolCompleto(tArbol* pa);
int arbolBalanceado(tArbol* pa);
int arbolAVL(tArbol* pa);
int arbolAVLR(tArbol* pa);
int arbolAVL2(tArbol* pa);

#endif // ARBOL_H_INCLUDED
