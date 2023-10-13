#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MENOR(X,Y) ((X) <= (Y)? (X):(Y))
#include "../bibliotecaEstructuras/colaDin.h"

int main(){
  tCola cola;
  int datos[] = {1,2,3,4,5,};
  char cad [20] = "AGUSTINA IACOBACCIO";
  char cadaux [20];
  int dato,i;
  crearCola(&cola);
  acolar(&cola,cad,strlen(cad)+1);
  for(i = 0 ; i < sizeof(datos)/sizeof(datos[0]) ; i++)
    acolar(&cola,&datos[i],sizeof(datos[0]));
  desacolar(&cola,cadaux,sizeof(cad));
  printf("%s\n",cadaux);
  for(i = 0 ; i < sizeof(datos)/sizeof(datos[0]) ; i++){
    desacolar(&cola,&dato,sizeof(datos[0]));
    printf("%d\n",dato);
  }

  return 0;
}
