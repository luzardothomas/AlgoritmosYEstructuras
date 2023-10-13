#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../bibliotecaEstructuras/pilaCircular.h"
int main(){
  int datos[] = {1,2,3,4,5};
  int i,dato;
  tPilaC pila;
  crearPila(&pila);
  for(i = 0 ; i < sizeof(datos)/sizeof(datos[0]) ; i++)
    apilar(&pila,&datos[i],sizeof(datos[0]));
/*
  for(i = 0 ; i < sizeof(datos)/sizeof(datos[0]) ; i++){
    desapilar(&pila,&dato,sizeof(datos[0]));
    printf("%d\n",dato);
  }
*/
  verTope(&pila,&dato,sizeof(dato));
  printf("Ver tope %d\n",dato);  printf("Esta vacia la pila? %d\n",pilaVacia(&pila));
  vaciarPila(&pila);
  printf("Esta vacia la pila? %d\n",pilaVacia(&pila));
  return 0;
}
