#include "indice.h"

void crearIndice(tIndice* pin, size_t tamClave, cmp comp){
  pin->comp = comp;
  pin->tamClave = tamClave;
  pin->ind = NULL;
}

int insertarIndice(tIndice* pin, void *clave, unsigned nroReg){
  indice* nue;
  indice* actual = pin->ind;

  tLista* pl = (tLista*)clave;
  tLista* menor = pl;
  tLista* lista = pl;
  tNodo* aux;
  tDato* dato;
  int comp;

  if(!*pl)
    return 0;

  lista = &(*lista)->sig;

  while(*lista){
    comp = pin->comp((*menor)->dato, (*lista)->dato);
    if(comp > 0)
      menor = lista;
    else if(comp == 0)
      return DUPLICADO;
    lista = &(*lista)->sig;
  }

  if(menor != pl){
    aux = *menor;
    *menor = aux->sig;

    aux->sig = *pl;
    *pl = aux;
  }

  dato = (*pl)->dato;

  nue = (indice*)malloc(sizeof(indice));

  if(nue == NULL)
    return 0;

  nue->clave = malloc(pin->tamClave);

  if(nue->clave == NULL){
    free(nue);
    return 0;
  }

  memcpy(nue->clave,&dato->nro,pin->tamClave);
  nue->nroReg = nroReg;
  nue->sig = NULL;

  if(pin->ind == NULL)
    pin->ind = nue;
  else{
    while(actual->sig)
      actual = actual->sig;
    actual->sig = nue;
  }


  return TODO_OK;
}

void mostrarIndice(const tIndice* pin, void (*mostrar)(const void*,FILE*),FILE* pf){
  indice* actual = pin->ind;
  while(actual){
    mostrar(actual,pf);
    actual = actual->sig;
  }
}

/*
void vaciarIndice(tIndice* pin){
  tNodoInd* aux = *pin;

  while(*pin){
    *pin = aux->sig;
    free(aux->dato);
    free(aux);
    aux = *pin;
  }

}





int eliminarIndice(tIndice* pin, void *clave, unsigned nroReg, cmp comp){

  tNodoInd* aux = *pin;
  if(*pin == NULL)
    return 0;

  while(*pin){
    if(comp((*pin)->dato,clave) == 0){
      aux = *pin;
      *pin = (*pin)->sig;
      free(aux->dato);
      free(aux);
    }
    else
      pin = &(*pin)->sig;
  }
  return 1;
}
*/

