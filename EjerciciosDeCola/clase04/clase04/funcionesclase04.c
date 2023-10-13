#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionesclase04.h"

void crearCola(tCola *pc){
  pc->ini = NULL;
  pc->fin = NULL;
}
int acolar(tCola* pc,const void* dato, size_t tam){
  tNodo* nue = (tNodo*)malloc(sizeof(tNodo));
  if(nue == NULL)
    return 0;
  nue->dato = malloc(tam);
  if(nue->dato == NULL){
    free(nue);
    return 0;
  }
  memcpy(nue->dato,dato,tam);
  nue->tam = tam;
  nue->sig = NULL;
  if(pc->ini == NULL)
    pc->ini = nue;
  else
    pc->fin->sig = nue;
  pc->fin = nue;
  return 1;
}
int desacolar(tCola* pc, void* dato, size_t tam){
  tNodo* aux = pc->ini;
  if(pc->ini == NULL)
    return 0;
  pc->ini = aux->sig;
  memcpy(dato,aux->dato,MENOR(aux->tam,tam));
  free(aux->dato);
  free(aux);
  return 1;
}
