#include "arbol.h"
void crearArbol(tArbol* pa){
  *pa = NULL;
}
int insertarArbol(tArbol* pa, const void* dato, size_t tam,cmp comp){
  tNodoArbol* nue;
  int comparar;

  while(*pa){

    comparar = comp((*pa)->dato,dato);

    if(comparar > 0)
      pa = &(*pa)->izq;
    else if(comparar < 0)
      pa = &(*pa)->der;
    else
      return DUPLICADO;

  }

  nue = (tNodoArbol*)malloc(sizeof(tNodoArbol));

  if(nue == NULL)
    return SIN_MEM;

  nue->dato = malloc(tam);

  if(nue->dato == NULL){
    free(nue);
    return SIN_MEM;
  }

  nue->tam = tam;
  nue->der = NULL;
  nue->izq = NULL;

  memcpy(nue->dato,dato,tam);

  *pa = nue;

  return TODO_OK;
}
int insertarArbolRecursivo(tArbol* pa, const void* dato, size_t tam,cmp comp){
  tNodoArbol* nue;

  if(*pa){

    if(comp((*pa)->dato,dato) > 0)
      return insertarArbol(&(*pa)->izq,dato,tam,comp);
    else if(comp((*pa)->dato,dato) < 0)
      return insertarArbol(&(*pa)->der,dato,tam,comp);
    else
      return DUPLICADO;

  }

  nue = (tNodoArbol*)malloc(sizeof(tNodoArbol));

  if(nue == NULL)
    return SIN_MEM;

  nue->dato = malloc(tam);

  if(nue->dato == NULL){
    free(nue);
    return SIN_MEM;
  }

  nue->tam = tam;
  nue->der = NULL;
  nue->izq = NULL;

  memcpy(nue->dato,dato,tam);

  *pa = nue;

  return TODO_OK;
}
///En orden IRD
void recorrerArbolEnOrden(const tArbol* pa, accion act, void* param){
  if(!*pa)
    return;

  recorrerArbolEnOrden(&(*pa)->izq,act,param);

  act((*pa)->dato,param);

  recorrerArbolEnOrden(&(*pa)->der,act,param);

}
///Pos orden IDR
void recorrerArbolPosOrden(const tArbol* pa, accion act, void* param){
  if(!*pa)
    return;
  recorrerArbolPosOrden(&(*pa)->izq,act,param);
  recorrerArbolPosOrden(&(*pa)->der,act,param);
  act((*pa)->dato,param);
}
///Pre orden RID
void recorrerArbolPreOrden(const tArbol* pa, accion act, void* param){
  if(!*pa)
    return;

  act((*pa)->dato,param);
  recorrerArbolPreOrden(&(*pa)->izq,act,param);
  recorrerArbolPreOrden(&(*pa)->der,act,param);
}
void vaciarArbol(tArbol* pa){
  if(!*pa)
    return;

  vaciarArbol(&(*pa)->izq);
  vaciarArbol(&(*pa)->der);
  free((*pa)->dato);
  free(*pa);
  *pa = NULL;
}
void podarNivel(tArbol* pa, int n){
  if(!*pa)
    return;

  podarNivel(&(*pa)->izq,n-1);
  podarNivel(&(*pa)->der,n-1);

  if(n < 0)
    vaciarArbol(pa);
}
int contarNodos(tArbol* pa){

  if(!*pa)
    return 0;

  return contarNodos(&(*pa)->izq) +
         contarNodos(&(*pa)->der) + 1;
}
int alturaNivel(tArbol* pa){
  int hi,hd;

  if(!*pa)
    return 0;

  hi = alturaNivel(&(*pa)->izq);
  hd = alturaNivel(&(*pa)->der);
  return MAYOR(hi,hd) + 1;
}
int mayor(tArbol* pa,void* dato, size_t tam){
  if(!*pa)
    return ARBOL_VACIO;

  while((*pa)->der)
    pa = &(*pa)->der;

  memcpy(dato,(*pa)->dato,MENOR((*pa)->tam,tam));

  return TODO_OK;
}
tArbol* mayorNodo(tArbol* pa){
  if(!*pa)
    return NULL;

  while((*pa)->der)
    pa = &(*pa)->der;

  return pa;
}
tArbol* menorNodo(tArbol* pa){
  if(!*pa)
    return NULL;

  while((*pa)->izq)
    pa = &(*pa)->izq;

  return pa;
}
int eliminarRaiz(tArbol* pa, void* dato,size_t tam){
  tNodoArbol* elim;
  tArbol* reemp;
  int hd,hi;

  if(!*pa)
    return ARBOL_VACIO;

  memcpy(dato,(*pa)->dato,MENOR((*pa)->tam,tam));

  free((*pa)->dato);

  if(!(*pa)->izq && !(*pa)->der){
    free(*pa);
    *pa = NULL;
    return TODO_OK;
  }

  hi = alturaNivel(&(*pa)->izq);
  hd = alturaNivel(&(*pa)->der);

  reemp = hi > hd ? mayorNodo(&(*pa)->izq) : menorNodo(&(*pa)->der);

  elim = *reemp;

  (*pa)->dato = elim->dato;
  (*pa)->tam = elim->tam;

  *reemp = elim->izq ? elim->izq : elim->der;

  free(elim);

  return TODO_OK;
}
/** vector [4,5,6,10,15,20]
*   pos     0 1 2 3  4  5
*           li          ls
*/
int cargarArbolOrdR(tArbol* pa, void* orig, size_t tam,int li, int ls){
  tNodoArbol* nue;
  int m = (li+ls)/2;
  int r;

  if(li > ls)
    return TODO_OK;

  nue = (tNodoArbol*)malloc(sizeof(tNodoArbol));

  if(nue == NULL)
    return SIN_MEM;

  nue->dato = malloc(tam);

  if(nue->dato == NULL){
    free(nue);
    return SIN_MEM;
  }

  memcpy(nue->dato,(char*)orig + (tam*m),tam);
  nue->tam = tam;
  nue->izq = NULL;
  nue->der = NULL;

  *pa = nue;

  if(((r = cargarArbolOrdR(&(*pa)->izq,orig,tam,li,m-1))) != TODO_OK)
    return r;

  return cargarArbolOrdR(&(*pa)->der,orig,tam,m+1,ls);
}
/// Mismo concepto pero Genérico
int cargarDatosOrdR(tArbol* pa, void* orig, size_t tam,int li, int ls,
                    int (*copiarDatoOrig)(void* dest,void* orig,size_t tam, int pos)){
  tNodoArbol* nue;
  int m = (li+ls)/2;
  int r;

  if(li > ls)
    return TODO_OK;

  nue = (tNodoArbol*)malloc(sizeof(tNodoArbol));

  if(nue == NULL)
    return SIN_MEM;

  nue->dato = malloc(tam);

  if(nue->dato == NULL){
    free(nue);
    return SIN_MEM;
  }

  memcpy(nue->dato,(char*)orig + (tam*m),tam);
  nue->tam = tam;
  nue->izq = NULL;
  nue->der = NULL;

  if(((r = copiarDatoOrig(nue->dato,orig,tam,m))) == 0)
    return r;

  *pa = nue;

  if(((r = cargarDatosOrdR(&(*pa)->izq,orig,tam,li,m-1,copiarDatoOrig))) != TODO_OK)
    return r;

  return cargarDatosOrdR(&(*pa)->der,orig,tam,m+1,ls,copiarDatoOrig);
}
int copiarDatoVec(void* dest,void* orig,size_t tam, int pos){
  memcpy(dest,(char*)orig + pos*tam,tam);
  return 1;
}
int copiarDatoArch(void* dest,void* orig,size_t tam, int pos){
  int r;
  FILE* pf = (FILE*)orig;
  fseek(pf,pos*tam,SEEK_SET);
  r = fread(dest,tam,1,pf);
  if(r != tam)
    return 0;
  return 1;
}
int cargarArbolArch(tArbol* pa, char* path, size_t tam){
  int cantReg,r;
  FILE* pf = fopen(path,"rb");
  if(!pf)
    return 0;
  fseek(pf,0L,SEEK_END);
  cantReg = ftell(pf)/tam;
  r = cargarDatosOrdR(pa,pf,tam,0,cantReg-1,copiarDatoArch);
  fclose(pf);
  return r;
}
int arbolCompletoHastaNivel(tArbol* pa,int n){

  if(n < 0)
    return 1;

  if(!*pa)
    return 0;

  return arbolCompletoHastaNivel(&(*pa)->izq,n-1) &&
         arbolCompletoHastaNivel(&(*pa)->der,n-1);
}
int arbolCompleto(tArbol* pa){
  int h = alturaNivel(pa);
  return arbolCompletoHastaNivel(pa,h-1);
}
int arbolBalanceado(tArbol* pa){
  int h = alturaNivel(pa);
  return arbolCompletoHastaNivel(pa,h-2);
}
int arbolAVL(tArbol* pa){
  int hi,hd;
  if(!*pa)
    return 1;

  hi = alturaNivel(&(*pa)->izq);
  hd = alturaNivel(&(*pa)->der);

  if(MOD(hi-hd) > 1)
    return 0;

  return arbolAVL(&(*pa)->izq) &&
         arbolAVL(&(*pa)->der);
}
int arbolAVLR(tArbol* pa){
  int hi,hd;

  if(!*pa)
    return 0;

  hi = arbolAVLR(&(*pa)->izq);
  hd = arbolAVLR(&(*pa)->der);

  if(hi == -1 || hd == -1 || MOD(hi-hd) > 1)
    return -1;

  return (hi > hd ? hi : hd) + 1;
}
int arbolAVL2(tArbol* pa){
  return arbolAVLR(pa) != -1;
}

