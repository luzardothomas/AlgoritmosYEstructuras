#include "pilaCircular.h"
void crearPila(tPilaC* pc){
  *pc = NULL;
}

///↓←←←←←←←←←←←←←←←←←←←←←←←←←
///→[***] -> [***] -> [***] ↑ (*pc)->sig
///                     ↑ *pc
int apilar(tPilaC* pc, const void* dato, size_t tam){
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

  if(*pc == NULL){
    nue->sig = nue;
    *pc = nue;
  }
  else{
    nue->sig = (*pc)->sig;
    (*pc)->sig = nue;
  }

  return 1;
}

int desapilar(tPilaC* pc,void* dato, size_t tam){
  tNodo* aux;
  if(*pc == NULL)
    return 0;
  aux = (*pc)->sig;
  memcpy(dato,aux->dato,minimo(aux->tam,tam));
  if(*pc == aux)
    *pc = NULL;
  else
    (*pc)->sig = aux->sig;
  free(aux->dato);
  free(aux);
  return 1;
}

void vaciarPila(tPilaC* pc){
  tNodo* aux;
  if(*pc == NULL)
    return;
  while((*pc)->sig != *pc){
    aux = (*pc)->sig;
    (*pc)->sig =  aux->sig;
    free(aux->dato);
    free(aux);
  }
  free((*pc)->dato);
  free(*pc);
  *pc = NULL;
}

int pilaVacia(const tPilaC* pc){
  return *pc == NULL;
}

int pilaLlena(const tPilaC* pc, size_t tam){
  tNodo* nue;
  nue = (tNodo*)malloc(sizeof(tNodo));
  nue->dato = malloc(tam);
  free(nue->dato);
  free(nue);
  return nue == NULL || nue->dato == NULL;
}

int verTope(const tPilaC* pc,void* dato ,size_t tam){
  if(*pc == NULL)
    return 0;
  memcpy(dato,(*pc)->sig->dato,minimo((*pc)->sig->tam,tam));
  return 1;
}

