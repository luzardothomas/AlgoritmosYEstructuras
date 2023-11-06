#include "indice.h"

tNodo* crearNodo(const void* dato,size_t tam){
  tNodo *nue;
  nue = (tNodo*)malloc(sizeof(tNodo));
  nue->dato = malloc(tam);

  if(!nue || !nue->dato){
    free(nue->dato);
    free(nue);
    return NULL;
  }

  memcpy(nue->dato,dato,tam);
  nue->tam = tam;
  nue->sig = NULL;

  return nue;
}

void crearIndice(tIndice* pin, size_t tamClave, cmp comp){
  pin->comp = comp;
  pin->tamClave = tamClave;
  pin->lista = NULL;
}

int insertarIndice(tIndice* pin, void *clave, unsigned nroReg){

  tRegistroIndice registroIndice;

  registroIndice.clave = malloc(pin->tamClave);

  if(!registroIndice.clave)
    return SIN_MEM;

  memcpy(registroIndice.clave,clave,pin->tamClave);

  registroIndice.nroReg = nroReg;

  if(!ponerEnOrden(&pin->lista, &registroIndice,sizeof(tRegistroIndice),pin->comp, NULL))
    return SIN_MEM;

  return TODO_OK;
}

void mostrarIndice(const tIndice* pin, void (*mostrar)(const void*,FILE*),FILE* pf){

  tLista *actual = (tLista*)&pin->lista;

  while(*actual){
    mostrar((*actual)->dato,pf);
    actual = &(*actual)->sig;
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

