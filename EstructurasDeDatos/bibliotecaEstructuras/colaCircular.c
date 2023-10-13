#include "colaCircular.h"
void crearCola(tColaC* cc){
  *cc = NULL;
}

void vaciarCola(tColaC* cc){
  tNodo* aux;
  if(*cc == NULL)
    return;
  while((*cc)->sig != *cc){
    aux = (*cc)->sig;
    (*cc)->sig = aux->sig;
    free(aux->dato);
    free(aux);
  }
  free(aux->dato);
  free(aux);
  *cc = NULL;
}

int acolar(tColaC* cc, const void* dato, size_t tam){
  tNodo* nue;
  nue = (tNodo*)malloc(sizeof(tNodo));
  if(nue == NULL)
    return 0;
  nue->dato = malloc(tam);
  if(nue->dato == NULL){
    free(nue);
    return 0;
  }
  memcpy(nue->dato,dato,tam);
  nue->tam = tam;

  if(*cc == NULL){
    nue->sig = nue;
    *cc = nue;
  }
  else{
    nue->sig = (*cc)->sig;
    (*cc)->sig = nue;
    *cc = nue;
  }
  return 1;
}
int desacolar(tColaC* cc,void* dato, size_t tam){
  tNodo* aux;
  if(*cc == NULL)
    return 0;
  aux = (*cc)->sig;
  memcpy(dato,aux->dato,minimo(aux->tam,tam));
  if(*cc == aux)
    *cc = NULL;
  else
    (*cc)->sig = aux->sig;
  free(aux->dato);
  free(aux);
  return 1;
}

int colaLlena(const tColaC *cc, size_t tam){
  tNodo* nue;
  nue = (tNodo*)malloc(sizeof(tNodo));
  nue->dato = malloc(tam);
  free(nue->dato);
  free(nue);
  return nue == NULL || nue->dato == NULL;
}

int colaVacia(const tColaC* cc){
  return *cc == NULL;
}

int verPrimero(tColaC* cc, void* dato, size_t tam){
  if(*cc == NULL)
    return 0;
  memcpy(dato,(*cc)->sig->dato,minimo((*cc)->sig->tam,tam));
  return 1;
}
