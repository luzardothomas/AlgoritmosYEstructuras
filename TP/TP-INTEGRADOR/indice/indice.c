#include "indice.h"
#include "../TP.h"

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

  if(!ponerEnOrden(&pin->lista, &registroIndice,sizeof(tRegistroIndice),pin->comp,NULL))
    return SIN_MEM;

  return TODO_OK;
}

int recorrerIndice(const tIndice* pin, accion action,void* param){
  tLista actual = pin->lista;
  tRegistroIndice registroIndice;

  if(!actual)
    return INDICE_VACIO;

  while(actual){
    registroIndice.nroReg = ((tRegistroIndice*)actual->dato)->nroReg;
    action(actual->dato,registroIndice.nroReg,param);
    actual = actual->sig;
  }

  return TODO_OK;
}

int buscarIndice(const tIndice* pin, void *clave, unsigned nroReg){
  tLista* lista = (tLista*)malloc(sizeof(tLista));
  tNodo* elim = NULL;
  tRegistroIndice registroIndice;

  registroIndice.clave = malloc(pin->tamClave);

  if(!ponerAlComienzo(lista,&registroIndice,sizeof(registroIndice))){
    free(registroIndice.clave);
    return SIN_MEM;
  }

  if(registroIndice.clave == NULL){
    free(elim->dato);
    free(elim);
    return SIN_MEM;
  }

  memcpy(registroIndice.clave,clave,pin->tamClave);

  elim = *lista;

  if((lista = buscarOcurrencia(&pin->lista,&registroIndice,pin->comp)) == pin->lista){
    free(elim->dato);
    free(elim);
    free(registroIndice.clave);
    return NO_ENCONTRADO;
  }

  memcpy(clave,(*lista)->dato,sizeof(tRegistroIndice));

  free(elim->dato);
  free(elim);
  free(registroIndice.clave);

  return ENCONTRADO;
}

void vaciarIndice(tIndice* pin){
  tNodo* aux = pin->lista;

  while(aux){
    pin->lista = aux->sig;
    free(aux->dato);
    free(aux);
    aux = pin->lista;
  }

}

int eliminarIndice(tIndice* pin, void *clave,unsigned nroReg){
  tLista* aux =  &pin->lista;
  tNodo* elim = pin->lista;

  tRegistroIndice registroIndice;
  int comp;

  if(!*aux)
    return 0;

  registroIndice.clave = malloc(pin->tamClave);

  if(!registroIndice.clave)
    return SIN_MEM;

  memcpy(registroIndice.clave,clave,pin->tamClave);

  while(*aux){
    comp = pin->comp((*aux)->dato,&registroIndice);
    if(comp == 0){
      elim = *aux;
      *aux = (*aux)->sig;
      memcpy(clave,elim->dato,sizeof(tRegistroIndice));
      free(elim->dato);
      free(elim);
    }
    aux = &(*aux)->sig;
  }
  free(registroIndice.clave);
  return 1;
}

int grabarIndice(const tIndice* pin, const char* path){
  FILE* pf;
  tLista* lista = (tLista*)&pin->lista;
  tRegistroIndice registroIndice;

  if(!abrirArchivo(&pf,path,"wb"))
    return ERROR_ARCH;

  registroIndice.clave = malloc(pin->tamClave);

  if(!registroIndice.clave)
    return SIN_MEM;

  if(!*lista)
    return INDICE_VACIO;

  while(*lista){

    memcpy(&registroIndice,(*lista)->dato,sizeof(registroIndice));

    fwrite(&registroIndice,sizeof(registroIndice),1,pf);

    lista = &(*lista)->sig;
  }

  free(registroIndice.clave);
  fclose(pf);

  return TODO_OK;
}

