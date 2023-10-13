#include "pilaDin.h"
void crearPila(tPila* pp){
  *pp = NULL;
}

int apilar(tPila* pp, const void* dato, size_t tam){
  tNodo* nuevo;
  nuevo = (tNodo*)malloc(sizeof(tNodo));
  if(nuevo == NULL){
    free(nuevo);
    return 0;
  }
  nuevo->dato = malloc(tam);
  if(nuevo->dato == NULL){
    free(nuevo->dato);
    free(nuevo);
    return 0;
  }
  memcpy(nuevo->dato,dato,tam);
  nuevo->tam = tam;
  nuevo->sig = *pp;
  *pp = nuevo;
  return 1;
}

int desapilar(tPila* pp, void* dato, size_t tam){
  tNodo* aux = *pp;
  if(*pp == NULL)
    return 0;
  memcpy(dato,aux->dato,MIN(tam,aux->tam));
  *pp = aux->sig;
  free(aux->dato);
  free(aux);
  return 1;
}

void vaciarPila(tPila* pp){
  tNodo* aux = *pp;
  while(aux != NULL){
    *pp = (*pp)->sig;
    free(aux->dato);
    free(aux);
    aux = *pp;
  }
}

int verTope(const tPila* pp, void* dato, size_t tam){
  if(*pp == NULL)
    return 0;
  memcpy(dato,(*pp)->dato,MIN(tam,(*pp)->tam));
  return 1;
}

int pilaVacia(const tPila* pp){
  return *pp == NULL;
}

int pilaLlena(const tPila *p,size_t tam){
  tNodo* aux = (tNodo*)malloc(sizeof(tNodo));
  void* info = malloc(tam);
  free(aux);
  free(info);
  return aux == NULL || info == NULL;
}
