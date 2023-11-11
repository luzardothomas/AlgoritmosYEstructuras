#include "indice.h"
#include "../TP.h"

void crearIndice(tIndice* pin, size_t tamClave, cmp comp){
  pin->comp = comp;
  pin->tamClave = tamClave;
  pin->lista = NULL;
  pin->regInd = malloc(pin->tamClave + sizeof(unsigned));
}
int insertarIndice(tIndice* pin, void *clave, unsigned nroReg){

  if(!pin->regInd)
    return SIN_MEM;

  memcpy(pin->regInd,clave,pin->tamClave);
  memcpy((char*)pin->regInd + pin->tamClave,&nroReg,sizeof(unsigned));

  if(!ponerEnOrden(&pin->lista,pin->regInd,pin->tamClave + sizeof(unsigned),pin->comp,NULL))
    return SIN_MEM;

  return TODO_OK;
}
int eliminarIndice(tIndice* pin, void *clave,unsigned* nroReg){

  if(!pin->regInd)
    return SIN_MEM;

  if(!pin->lista)
    return 0;

  return eliminarPorClave(&pin->lista,clave,pin->comp);
}
int buscarIndice(const tIndice* pin, void *clave, unsigned* nroReg){
  tNodo* buscar = NULL;

  if(!pin->regInd)
    return SIN_MEM;

  memcpy(pin->regInd,clave,pin->tamClave);
  memcpy((char*)pin->regInd + pin->tamClave,nroReg,sizeof(unsigned));

  if(!(buscar = buscarOcurrencia(&pin->lista,clave,pin->comp)))
    return NO_ENCONTRADO;

  memcpy(nroReg,(char*)buscar->dato + pin->tamClave,sizeof(unsigned));

  return ENCONTRADO;
}
int cargarIndice(tIndice* pin, const char* path){
  FILE* pf;
  long int clave;
  unsigned nroReg;

  if(!abrirArchivo(&pf,path,"rb"))
    return ERROR_ARCH;

  if(!pin->regInd)
    return SIN_MEM;

  fread(pin->regInd,pin->tamClave + sizeof(unsigned),1,pf);

  memcpy(&clave,pin->regInd,pin->tamClave);
  memcpy(&nroReg,(char*)pin->regInd + pin->tamClave,sizeof(unsigned));

  while(!feof(pf)){

    insertarIndice(pin,&clave,nroReg);

    fread(pin->regInd,pin->tamClave + sizeof(unsigned),1,pf);

    memcpy(&clave,pin->regInd,pin->tamClave);
    memcpy(&nroReg,(char*)pin->regInd + pin->tamClave,sizeof(unsigned));
  }

  return TODO_OK;
}
int grabarIndice(const tIndice* pin, const char* path){
  FILE* pf;
  tLista* lista = (tLista*)&pin->lista;

  if(!pin->regInd)
    return SIN_MEM;

  if(!abrirArchivo(&pf,path,"wb"))
    return ERROR_ARCH;


  if(!*lista)
    return INDICE_VACIO;

  while(*lista){

    memcpy(pin->regInd,(*lista)->dato,pin->tamClave);
    memcpy((char*)pin->regInd + pin->tamClave,(char*)(*lista)->dato + pin->tamClave,sizeof(unsigned));

    fwrite(pin->regInd,pin->tamClave + sizeof(unsigned),1,pf);

    lista = &(*lista)->sig;
  }

  fclose(pf);

  return TODO_OK;
}
void vaciarIndice(tIndice* pin){
  vaciarLista(&pin->lista);
  free(pin->regInd);
}
int recorrerIndice(const tIndice* pin, accion action,void* param){
  tLista actual = pin->lista;
  unsigned nroReg;

  if(!pin->regInd)
    return SIN_MEM;

  if(!actual)
    return INDICE_VACIO;

  while(actual){
    memcpy(pin->regInd,param,pin->tamClave);
    memcpy((char*)pin->regInd + pin->tamClave,&nroReg,sizeof(unsigned));
    action(actual->dato,nroReg,param);
    actual = actual->sig;
  }

  return TODO_OK;
}

