#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAY(X,Y) ((X) >= (Y)? (X):(Y))
#include "../../EstructurasDeDatos/bibliotecaEstructuras/pilaDin.h"
#include "implementacion.h"
int main(){

  tPila pila1,pila2,pila3;
  char cad1[] = "1972";
  char cad2[] = "51";
  char p;
  int i,may,carry;

  crearPila(&pila1);
  crearPila(&pila2);
  crearPila(&pila3);

  ///Apilo en ambas pilas

  for(i = 0 ; i < sizeof(cad1)-1 ; i++)
    apilar(&pila1,&cad1[i],sizeof(char));

  for(i = 0 ; i < sizeof(cad2)-1 ; i++)
    apilar(&pila2,&cad2[i],sizeof(char));

  ///Guardo el tamaño del número más grande menos uno por '\0'

  i = MAY(sizeof(cad1)-1,sizeof(cad2)-1);

  /// Leo hasta que el indice menor al '\0' por eso sumo uno

  may = i+1;

  ///Devuelvo el carry para tener en cuenta si el resultado tiene un número más

  carry = sumarNumerosGrandes(&pila1,&pila2,&pila3,i,cad1,cad2);

  printf("RESULTADO:");

  for(i = 0 ; i < may+carry-1 ; i++){
    desapilar(&pila3,&p,sizeof(char));
    printf("%c",p);
  }
  return 0;
}
