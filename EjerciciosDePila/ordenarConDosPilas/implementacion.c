#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "implementacion.h"
int ordenarConDosPilas(tPila* pmenor,tPila* pmayor,const void* valor,size_t tam,int cmp(const void*,const void*)){
  void* i = malloc(tam);
  if(i == NULL)
    return 0;

  ///Si hay datos en la pila Y
  ///el valor es menor al tope:
  ///DESAPILAR EL TOPE Y CARGARLO EN LA OTRA PILA

  while(verTope(pmayor,i,tam) && cmp(valor,i) > 0){
    desapilar(pmayor,i,tam);
    apilar(pmenor,i,tam);
  }

  ///Si hay datos en la pila Y
  ///el valor es mayor al tope:
  ///DESAPILAR EL TOPE Y CARGARLO EN LA OTRA PILA

  while(verTope(pmenor,i,tam) && cmp(valor,i) < 0){
    desapilar(pmenor,i,tam);
    apilar(pmayor,i,tam);
  }

  ///Si el valor era menor al tope de la pilamenor entonces cargalo en esta pila
  ///Caso contrario en pilamayor

  if(cmp(valor,i) < 0)
    apilar(pmenor,valor,tam);
  else
    apilar(pmayor,valor,tam);

  free(i);
  return 1;
}
