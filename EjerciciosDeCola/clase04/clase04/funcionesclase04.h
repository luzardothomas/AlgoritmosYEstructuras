#ifndef FUNCIONESCLASE04_H_INCLUDED
#define FUNCIONESCLASE04_H_INCLUDED

#define MENOR(X,Y) ((X) < (Y) ? (X):(Y))

typedef struct sNodo{
  void* dato;
  size_t tam;
  struct sNodo* sig;
}tNodo;

typedef struct{
    tNodo* ini;
    tNodo* fin;
}tCola;

typedef struct{
  int nro_ped;
  char cod[50];
  int cant;
  float precio;
}tPedido;

typedef struct{
  char cod[50];
  int cant;
  float precio;
}tStock;


void crearCola(tCola *pc);
int acolar(tCola* pc,const void* dato, size_t tam);
int desacolar(tCola* pc, void* dato, size_t tam);



#endif // FUNCIONESCLASE04_H_INCLUDED
