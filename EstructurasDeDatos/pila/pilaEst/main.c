#include <stdio.h>
#include <stdlib.h>
#include <string.h>




int main(){
  tPila pila;
  int datos[] = {1,2,3,4,5},i;
  char cad[20] = "Hola";
  char cadaux[20];
  int dato = 0;
  crearPila(&pila);
  for(i = 0 ; i < sizeof(datos)/sizeof(datos[0]) ; i++)
    apilar(&pila,&datos[i],sizeof(datos[0]));
  apilar(&pila,cad,strlen(cad)+1);
  desapilar(&pila,cadaux,sizeof(cad));
  printf("%s\n",cadaux);
  for(i = 0 ; i < sizeof(datos)/sizeof(datos[0]) ; i++){
    desapilar(&pila,&dato,sizeof(datos[0]));
    printf("%d\n",dato);
  }
  return 0;
}
