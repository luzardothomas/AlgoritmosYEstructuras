#include "indice.h"

void crearIndice(tIndice* pin){
  *pin = NULL;
}

void vaciarIndice(tIndice* pin){
  tNodoInd* aux = *pin;

  while(*pin){
    *pin = aux->sig;
    free(aux->dato);
    free(aux);
    aux = *pin;
  }

}

int mostrarIndice(const tIndice* pin, void (*mostrar)(const void*,FILE*),FILE* pf){
  int cant = 0;
  while(*pin){
    mostrar((*pin)->dato,pf);
    pin = &(*pin)->sig;
    cant++;
  }
  return cant;
}

int insertarIndice(tIndice* pin, void *clave, unsigned nroReg){
  tNodoInd* nue;
  return TODO_OK;
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


