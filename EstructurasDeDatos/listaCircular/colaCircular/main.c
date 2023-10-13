#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../bibliotecaEstructuras/colaCircular.h"
int main(){
  tColaC cola;
  int datos[] = {1,2,3,4,5},dato,i;
  crearCola(&cola);
  for(i = 0 ; i < sizeof(datos)/sizeof(datos[0]) ; i++)
    acolar(&cola,&datos[i],sizeof(datos[0]));
  printf("%d\n",colaVacia(&cola));
  verPrimero(&cola,&dato,sizeof(dato));
  printf("Dato:%d\n",dato);
  vaciarCola(&cola);
  printf("%d\n",colaVacia(&cola));
  /*
  for(i = 0 ; i < sizeof(datos)/sizeof(datos[0]) ; i++){
    desacolar(&cola,&dato,sizeof(dato));
    printf("%d\n",dato);
  }
  */
  return 0;
}
