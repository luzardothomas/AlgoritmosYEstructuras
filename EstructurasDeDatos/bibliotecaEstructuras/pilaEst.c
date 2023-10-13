#include "pilaEst.h"

void crearPila(tPila* pp){
  pp->tope = TAM_PILA;
}

int apilar(tPila* pp, const void* dato, size_t tam){
  if(pp->tope < tam+sizeof(size_t))
    return 0;///Pila llena

  pp->tope -= tam;
  memcpy(pp->pila + pp->tope,dato,tam);
  pp->tope -= sizeof(size_t);
  memcpy(pp->pila + pp->tope,&tam,sizeof(size_t));

  return 1;
}
int desapilar(tPila* pp, void* dato, size_t tam){
  size_t tamdp;

  if(pp->tope == TAM_PILA)
    return 0;///Pila vacia

  memcpy(&tamdp, pp->pila + pp->tope, sizeof(size_t));
  pp->tope += sizeof(tam);
  memcpy(dato,pp->pila + pp->tope,MENOR(tam, tamdp));
  pp->tope += tamdp;

  return 1;
}

int verTope(const tPila* pp, void* dato, size_t tam){
  size_t tamdp;
  if(pp->tope == TAM_PILA)
    return 0;///Pila vacia
  ///20 -> 15 -> 11
  ///pila + tope + size_t para apuntar al dato
  memcpy(&tamdp, pp->pila + pp->tope, sizeof(size_t));
  memcpy(dato,pp->pila + pp->tope + sizeof(size_t) ,MENOR(tamdp,tam));

  return 1;
}

void vaciarPila(tPila* pp){
  pp->tope = TAM_PILA;
}

int pilaVacia(const tPila* pp){
  return pp->tope == TAM_PILA;
}

int pilaLlena(const tPila *p,size_t tam){
  return pp->tope == 0;
}

