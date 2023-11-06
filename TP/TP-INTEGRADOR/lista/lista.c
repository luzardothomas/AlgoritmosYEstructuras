#include "lista.h"
typedef int (*cmp)(const void*,const void*);
void crearLista(tLista* pl){
  *pl = NULL;
}

int ponerAlComienzo(tLista* pl, const void* dato, size_t tam){
  tNodo* nue;
  nue = (tNodo*)malloc(sizeof(tNodo));
  if(nue == NULL)
    return 0;
  nue->dato = malloc(tam);
  if(nue->dato == NULL){
    free(nue);
    return 0;
  }
  nue->tam = tam;
  memcpy(nue->dato,dato,tam);
  nue->sig = *pl;
  *pl = nue;
  return 1;
}

int sacarPrimeroLista(tLista* pl, void* dato, size_t tam){
  tNodo* aux = *pl;
  if(aux == NULL)
    return 0;
  memcpy(dato,aux->dato,minimo(aux->tam,tam));
  free(aux->dato);
  free(aux);
  *pl = aux->sig;
  return 1;
}

int verPrimeroLista(const tLista* pl, void* dato, size_t tam){
  if(*pl == NULL)
    return 0;
  memcpy(dato,(*pl)->dato,minimo((*pl)->tam,tam));
  return 1;
}

int ponerAlFinal(tLista* pl, const void* dato, size_t tam){
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
  nue->sig = NULL;

  while(*pl)
    pl = &(*pl)->sig;

  *pl = nue;
  return 1;
}

int sacarUltimoLista(tLista* pl, void* dato, size_t tam){
  if(*pl == NULL)
    return 0;

  while((*pl)->sig)
    pl = &(*pl)->sig;

  memcpy(dato,(*pl)->dato,minimo((*pl)->tam,tam));
  free((*pl)->dato);
  free((*pl));
  *pl = NULL;
  return 1;
}

int verUltimoLista(const tLista* pl, void* dato, size_t tam){
  if(*pl == NULL)
    return 0;

  while((*pl)->sig)
    pl = &(*pl)->sig;

  memcpy(dato,(*pl)->dato,minimo((*pl)->tam,tam));
  return 1;
}

int listaVacia(const tLista* pl){
  return *pl == NULL;
}

int listaLlena(const tLista* pl , size_t tam){
  tNodo* nue;
  nue = (tNodo*)malloc(sizeof(tNodo));
  nue->dato = malloc(tam);
  free(nue);
  free(nue->dato);
  return nue == NULL || nue->dato == NULL;
}

void vaciarLista(tLista* pl){
  tNodo* aux = *pl;
  while(*pl){
    *pl = aux->sig;
    free(aux->dato);
    free(aux);
    aux = *pl;
  }
}

int mostrarLista(const tLista* pl, void (*mostrar)(const void*,FILE*),FILE* pf){
  int cant = 0;
  while(*pl){
    mostrar((*pl)->dato,pf);
    pl = &(*pl)->sig;
    cant++;
  }
  return cant;
}

int mostrarListaYVaciar(tLista* pl, void (*mostrar)(const void*,FILE*),FILE* pf){
  int cant = 0;
  tNodo* aux = *pl;
  while(*pl){
    if(mostrar && pf)
      mostrar((*pl)->dato,pf);
    aux = *pl;
    *pl = aux->sig;
    free(aux->dato);
    free(aux);
    cant++;
  }

  return cant;
}


int mostrarListaAlReves(const tLista* pl, void (*mostrar)(const void*,FILE*),FILE* pf){
  int cant = 0;
  if(*pl){
    cant = mostrarListaAlReves(&(*pl)->sig,mostrar,pf);
    mostrar((*pl)->dato,pf);
    return cant + 1;
  }
  return 0;
}

int mostrarListaAlRevesYVaciar(tLista* pl, void (*mostrar)(const void*,FILE*),FILE* pf){
  int cant = 0;
  if(*pl){
    cant = mostrarListaAlReves(&(*pl)->sig,mostrar,pf);
    mostrar((*pl)->dato,pf);
    free((*pl)->dato);
    free(*pl);
    *pl = NULL;
    return cant + 1;
  }
  return 0;
}

int ponerEnOrden(tLista* pl,const void* dato, size_t tam,
                 cmp comp,
                 int(*acumular)(void**,size_t*,const void*,size_t)){
  tNodo* nue;

  while(*pl && comp((*pl)->dato,dato) < 0)
    pl = &(*pl)->sig;

  if(*pl && comp((*pl)->dato,dato) == 0)
    return 2;

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
  nue->sig = *pl;
  *pl = nue;
  return 1;
}

void ordenar(tLista* pl, int(*cmp)(const void*,const void*)){
  tLista* ini = pl;
  tLista* q;
  tNodo* aux;

  if(*pl == NULL)
    return;

  while((*pl)->sig){
    if(cmp((*pl)->dato,(*pl)->sig->dato) > 0){
      q = ini;

      aux = (*pl)->sig;

      (*pl)->sig = aux->sig;

      while(cmp(aux->dato,(*q)->dato) > 0)
        q = &(*q)->sig;
      aux->sig = *q;
      *q = aux;
    }
    else
      pl = &(*pl)->sig;
  }
}

tLista* buscarMenor(tLista* pl, int (*cmp)(const void*, const void*)){
  tLista* menor = pl;

  pl = &(*pl)->sig;

  while(*pl){
    if(cmp((*menor)->dato, (*pl)->dato) > 0)
      menor = pl;
    pl = &(*pl)->sig;
  }

  return menor;
}
void ordenarLista(tLista* pl, int (*cmp)(const void*, const void*)) {
  tLista* menor;
  tNodo* aux;

  if(*pl == NULL)
    return;

  while((*pl)->sig){

    menor = buscarMenor(pl,cmp);

    if(menor != pl){
      aux = *menor;
      *menor = aux->sig;

      aux->sig = *pl;
      *pl = aux;
    }
    pl = &(*pl)->sig;
  }
}

tLista* buscarOcurrencias(tLista* pl,const void* ocur,int(*cmp)(const void*,const void*)){
  tLista* buscar = pl;
  pl = &(*pl)->sig;
  while(*pl){
    if(cmp((*pl)->dato,ocur) == 0)
      buscar = pl;
    pl = &(*pl)->sig;
  }
  return buscar;
}

int agrupar(tLista* pl, int(*cmp)(const void*,const void*), int (*acum)(void*,const void*)){
  tLista* buscar;

  if(*pl == NULL)
    return 0;

  while((*pl)->sig){

    buscar = buscarOcurrencias(pl,(*pl)->dato,cmp);

    if(buscar != pl){
      acum((*pl)->dato,(*buscar)->dato);
      free((*buscar)->dato);
      free(*buscar);
      *buscar = (*buscar)->sig;
    }
    else
      pl = &(*pl)->sig;
  }
  return 1;
}

int eliminarPorClave(tLista* pl,const void* dato,int(*cmp)(const void*,const void*)){
  tNodo* aux = *pl;
  if(*pl == NULL)
    return 0;

  while(*pl){
    if(cmp((*pl)->dato,dato) == 0){
      aux = *pl;
      *pl = (*pl)->sig;
      free(aux->dato);
      free(aux);
    }
    else
      pl = &(*pl)->sig;
  }
  return 1;
}

void reduceList(tLista* pl,void* acu, void (*acum)(void*,const void*)){
  while(*pl){
    acum(acu,(*pl)->dato);
    pl = &(*pl)->sig;
  }
}

int filterList(tLista* pl,void* comp, int (*cmp)(const void*,const void*)){
  tNodo* aux;
  int contElim = 0;
  while(*pl){

    if(cmp((*pl)->dato,comp) >= 0)
      pl = &(*pl)->sig;
    else{
      aux = (*pl)->sig;
      free((*pl)->dato);
      free(*pl);
      *pl = aux;
      contElim++;
    }
  }
  return contElim;
}

