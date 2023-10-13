#include "colaDin.h"

/// |***| -> |***| -> |***| -> NULL
///  INI               FIN

void crearCola(tCola* pc){
  pc->ini = NULL;
  pc->fin = NULL;
}

int acolar(tCola* pc, const void* dato, size_t tam){
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

  memcpy(dato,pc->ini->dato,MENOR(pc->ini->tam,tam));

  free(pc->ini->dato);
  free(pc->ini);

  pc->ini = aux->sig;

  return 1;
}

int colaVacia(const tCola* pc){
  return pc->ini == NULL;
}

void vaciarCola(tCola *pc){
  tNodo* elim = pc->ini;

  while(elim){
    pc->ini = elim->sig;
    free(elim->dato);
    free(elim);
    elim = pc->ini;
  }
  pc->fin = NULL;
}

int verPrimeroCola(tCola *pc,void* dato,size_t tam){
  if(pc->ini == NULL)
    return 0;

  memcpy(dato,pc->ini->dato,MENOR(tam,pc->ini->tam));

  return 1;
}

int colaLlena(const tCola* pc,size_t tam){
  tNodo* nue;
  nue = (tNodo*)malloc(sizeof(tNodo));
  nue->dato = malloc(tam);
  free(nue->dato);
  free(nue);
  return nue == NULL || nue->dato == NULL;

}

