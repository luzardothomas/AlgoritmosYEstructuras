#include "listaDoble.h"
void crearLista(tLista* pl){
  *pl = NULL;
}

void vaciarLista(tLista* pl){
  tNodo* aux;
  if(*pl == NULL)
    return;
  while(*pl){
    aux = *pl;
    *pl = aux->sig;
    free(aux->dato);
    free(aux);
  }
}

int listaVacia(const tLista* pl){
  return *pl == NULL;
}

int listaLlena(const tLista* pl, size_t tam){
  tNodo* nue;
  nue = (tNodo*)malloc(sizeof(tNodo));
  nue->dato = malloc(tam);
  free(nue->dato);
  free(nue);
  return nue == NULL || nue->dato == NULL;
}
int ponerAlComienzo(tLista* pl,const void* dato, size_t tam){
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
  nue->ant = NULL;

  if(*pl == NULL)
    nue->sig = NULL;
  else{
    while((*pl)->ant)
      pl = &(*pl)->ant;
    (*pl)->ant = nue;
    nue->sig = *pl;
  }
  *pl = nue;
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
  nue->tam = tam;
  memcpy(nue->dato,dato,tam);
  nue->sig = NULL;

  if(*pl == NULL)
    nue->ant = NULL;
  else{
    while((*pl)->sig)
      pl = &(*pl)->sig;
    (*pl)->sig = nue;
    nue->ant = *pl;
  }
  *pl = nue;
  return 1;
}

int mostrarDeIzquierdaADerecha(tLista* pl, void(*mostrar)(const void*)){
  int cont = 0;
  tNodo* act = *pl;
  if(act == NULL)
    return 0;

  while(act->ant)
    act = act->ant;

  while(act->sig){
    cont++;
    mostrar(act->dato);
    act = act->sig;
  }

  mostrar(act->dato);

  *pl = act;

  return cont;
}




int mostrarDeDerechaAIzquierda(tLista* pl, void(*mostrar)(const void*)){
  int cont = 0;
  tNodo* act = *pl;

  if(act == NULL)
    return 0;

  while(act->sig)
    act = act->sig;

  while(act->ant){
    cont++;
    mostrar(act->dato);
    act = act->ant;
  }

  mostrar(act->dato);

  *pl = act;

  return cont;
}

int ponerEnOrden(tLista* pl, const void* dato, size_t tam, int (*cmp)(const void*, const void*)){
    tNodo *nue,
          *auxSig = *pl,
          *auxAnt =auxSig?auxSig->ant:NULL;

    while(auxAnt && cmp(dato,auxAnt->dato)<0){
        auxSig = auxAnt;
        auxAnt = auxAnt->ant;
    }
    while(auxSig && cmp(dato,auxSig->dato)>0){
        auxAnt = auxSig;
        auxSig = auxSig->sig;
    }

    if((auxSig && cmp(dato,auxSig->dato) == 0)||
       (auxAnt && cmp(dato,auxAnt->dato) == 0))
      return DUPLICADO;

    nue = (tNodo*)malloc(sizeof(tNodo));

    if (nue == NULL)
      return 0;

    nue->dato = malloc(tam);

    if (nue->dato == NULL){
      free(nue);
      return 0;
    }

    nue->tam = tam;
    memcpy(nue->dato,dato,tam);
    nue->sig = auxSig;
    nue->ant = auxAnt;

    if(auxAnt)
      auxAnt->sig = nue;

    if(auxSig)
      auxSig->ant = nue;

    *pl = nue;
    return OK;
}

tLista* buscarMenor(tLista* pl,int (*cmp)(const void*,const void*)){
  tLista* menor = pl;
  pl = &(*pl)->sig;
  while(*pl){
    if(cmp((*pl)->dato,(*menor)->dato) < 0)
      menor = pl;
    pl = &(*pl)->sig;
  }
  return menor;
}

void ordenarLista(tLista* pl,int (*cmp)(const void*,const void*)){
  tLista* menor;
  tNodo* aux;

  ///Lista vacía

  if(*pl == NULL)
    return;

  ///Te moves al inicio de la lista si es que no lo estas

  while((*pl)->ant)
    pl = &(*pl)->ant;

  ///Buscas el primer menor para ponerle el anterior como nulo

  menor = buscarMenor(pl,cmp);
  (*menor)->ant = NULL;

  ///No hace falta analizar el último porque ya te queda acomodado

  while((*pl)->sig){

    ///Aux guarda *pl o un supuesto *menor
    aux = *menor;

    ///Si hay menor:
    ///El siguiente del nodo al que apunta a menor lo reapuntas al siguiente del menor
    ///El siguiente del menor le guardas la dirección de *pl
    ///Haces que *pl se reapunte al nodo del menor

    if(menor != pl){
      *menor = aux->sig;
      aux->sig = *pl;
      *pl = aux;
    }

    ///Te moves al siguiente porque el anterior ya lo acomodaste

    pl = &(*pl)->sig;

    ///Buscas el nuevo menor

    menor = buscarMenor(pl,cmp);

    ///El anterior del menor actual es el menor anterior

    (*menor)->ant = aux;
  }
}

tLista* buscarOcurrencia(tLista* pl, int (*cmp)(const void*,const void*)){
  tLista* buscar = pl;
  pl = &(*pl)->sig;
  while(*pl){
    if(cmp((*pl)->dato,(*buscar)->dato) == 0)
      buscar = pl;
    pl = &(*pl)->sig;
  }
  return buscar;
}

int agrupar(tLista* pl, int (*cmp)(const void*,const void*),int (*acum)(void*,const void*)){
  tLista* buscar;
  tNodo* aux;

  ///Lista vacía

  if(*pl == NULL)
    return 0;

  ///Te moves al inicio de la lista si es que no lo estas

  while((*pl)->ant)
    pl = &(*pl)->ant;

  ///Si el siguiente del actual es nulo, es porque no hay más ocurrencias

  while((*pl)->sig){
    ///Busco la ocurrencia del dato actual

    buscar = buscarOcurrencia(pl,cmp);

    ///Guardo el buscar en aux por si hubo ocurrencia o no

    aux = *buscar;

    ///Si hubo ocurrencia:
    ///Acumulo y reapunto el siguiente del nodo que apunta a buscar con el siguiente del buscar
    ///Por último elimino el nodo que ya se utilizó
    ///Sino muevo el pl porque ya no hay ocurrencias del primer dato y tras moverse
    ///El anterior del actual tiene que ser el nodo anterior que se guardó en aux

    if(buscar != pl){
      acum((*pl)->dato,(*buscar)->dato);
      *buscar = aux->sig;
      free(aux->dato);
      free(aux);
    }
    else{
      pl = &(*pl)->sig;
      (*pl)->ant = aux;
    }
  }
  return 1;
}

int eliminarPorClave(tLista* pl, const void* comp,int (*cmp)(const void*,const void*)){
  int cont = 0;
  tNodo* aux;
  tNodo* ant;

  ///Lista vacía

  if(*pl == NULL)
    return 0;

  ///Te moves al inicio de la lista si es que no lo estas

  while((*pl)->ant)
    pl = &(*pl)->ant;

  ///Busco la primer ocurrencia de la clave

  while(*pl && !(cmp((*pl)->dato,comp))){
    aux = *pl;
    cont++;
    *pl = aux->sig;
    free(aux->dato);
    free(aux);
  }

  ///Al encontrarla pongo el primer anterior nulo y paso al siguiente

  if(*pl){
    (*pl)->ant = NULL;
    ant = *pl;
    pl = &(*pl)->sig;
  }

  while(*pl){

    ///El anterior del actual le pongo la ocurrencia anterior y me muevo al siguiente
    ///Sino elimino y reapunto *pl al siguiente

    if(cmp((*pl)->dato,comp)){
      (*pl)->ant = ant;
      ant = *pl;
      pl = &(*pl)->sig;
    }
    else{
      aux = *pl;
      cont++;
      *pl = aux->sig;
      free(aux->dato);
      free(aux);
    }
  }
  return cont;
}



int filter(tLista* pl,const void* comp,int (*cmp)(const void*,const void*)){
  int cont = 0;
  tNodo* aux;
  tNodo* ant;

  ///Lista vacía

  if(*pl == NULL)
    return 0;

  ///Te moves al inicio de la lista si es que no lo estas

  while((*pl)->ant)
    pl = &(*pl)->ant;


  ///Busco la primer ocurrencia a filtrar

  while(*pl && !(cmp((*pl)->dato,comp) > 0)){
    aux = *pl;
    cont++;
    *pl = aux->sig;
    free(aux->dato);
    free(aux);
  }

  ///Al encontrarla pongo el primer anterior nulo y paso al siguiente

  if(*pl){
    (*pl)->ant = NULL;
    ant = *pl;
    pl = &(*pl)->sig;
  }

  while(*pl){

    ///El anterior del actual le pongo la ocurrencia anterior y me muevo al siguiente
    ///Sino elimino y reapunto *pl al siguiente

    if(cmp((*pl)->dato,comp) > 0){
      (*pl)->ant = ant;
      ant = *pl;
      pl = &(*pl)->sig;
    }
    else{
      aux = *pl;
      cont++;
      *pl = aux->sig;
      free(aux->dato);
      free(aux);
    }
  }
  return cont;
}

int reduce(tLista* pl,void* acum,int (*facum)(void*,const void*)){
  int cont = 0;

  if(*pl == NULL)
    return 0;

  ///Te moves al inicio de la lista si es que no lo estas

  while((*pl)->ant)
    pl = &(*pl)->ant;

  while(*pl){
    cont++;
    facum(acum,(*pl)->dato);
    pl = &(*pl)->sig;
  }
  return cont;
}

int sacarPrimero(tLista* pl,void* dato, size_t tam){
  tNodo* aux;
  if(*pl == NULL)
    return 0;
  aux = *pl;
  memcpy(dato,aux->dato,minimo(aux->tam,tam));
  if((*pl)->sig){
    *pl = (*pl)->sig;
    (*pl)->ant = aux->ant;
  }
  else
    *pl = NULL;

  free(aux->dato);
  free(aux);
  return 1;
}

int sacarUltimo(tLista* pl,void* dato, size_t tam){
  tNodo* aux;
  if(*pl == NULL)
    return 0;

  while((*pl)->sig)
    pl = &(*pl)->sig;

  aux = *pl;

  memcpy(dato,aux->dato,minimo(aux->tam,tam));

  *pl = NULL;
  free(aux->dato);
  free(aux);
  return 1;
  ///    NULL
  /// ↓ [****] ↑
  /// ↓ [****] ↑
  /// ↓ [****] ↑
  /// ↓ [****] ↑
  /// ↓ [****] ↑
  ///    NULL
}




