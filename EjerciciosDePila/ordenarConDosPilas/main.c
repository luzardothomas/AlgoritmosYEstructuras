#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../EstructurasDeDatos/bibliotecaEstructuras/pilaDin.h"
#include "implementacion.h"

int compararEnteros(const void* a, const void* b){
  int* pa = (int*)a,*pb = (int*)b;
  return *pa-*pb;
}

int main(){

  tPila pmenor,pmayor;
  int valor = 0,i;
  int menor[] = {1,2,5,9};
  int mayor[] = {19,16,15};

  crearPila(&pmenor);
  crearPila(&pmayor);

  ///::::::::::::::::::: PRUEBA EN EL MAIN :::::::::::::::::::

  ///Cargar datos en la pila

  for(i = 0 ; i < sizeof(menor)/sizeof(menor[0]) ; i++)
    apilar(&pmenor,&menor[i],sizeof(menor[0]));

  for(i = 0 ; i < sizeof(mayor)/sizeof(mayor[0]) ; i++)
    apilar(&pmayor,&mayor[i],sizeof(mayor[0]));

  ordenarConDosPilas(&pmenor,&pmayor,&valor,sizeof(valor),compararEnteros);

  ///Mostrar datos en orden ascendente

  printf("ORDEN ASCENDENTE\n");
  while(desapilar(&pmenor,&i,sizeof(menor[0]))){
    apilar(&pmayor,&i,sizeof(mayor[0]));
  }
  while(desapilar(&pmayor,&i,sizeof(mayor[0]))){
    apilar(&pmenor,&i,sizeof(menor[0]));
    printf("%d ",i);
  }
  printf("\n");
  printf("ORDEN DESCENDENTE\n");

  ///Mostrar datos en orden descendente

  while(desapilar(&pmenor,&i,sizeof(menor[0]))){
    printf("%d ",i);
  }
  return 0;
}
