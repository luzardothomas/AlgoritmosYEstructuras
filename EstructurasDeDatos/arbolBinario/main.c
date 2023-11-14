#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecaEstructuras/arbol.h"
int compararEnteros(const void*a, const void*b){
  int* pa = (int*)a;
  int* pb = (int*)b;
  return *pa-*pb;
}
void mostrarEnteros(void* a,void*b){
  int* pa = (int*)a;
  printf("%d\n",*pa);
}
int main(){
  int datos1[] = {10,5,4,6,20,15};
  int datos2[] = {4,5,6,10,15,20};
  int vector[] = {4,5,6,10,15,20,25};
  int dato;
  int i;
  tArbol arbol1;
  tArbol arbol2;
  tArbol arbol3;

  crearArbol(&arbol1);
  crearArbol(&arbol2);
  crearArbol(&arbol3);

  for(i = 0 ; i < sizeof(datos1)/sizeof(datos1[0]) ; i++)
    insertarArbolRecursivo(&arbol1,&datos1[i],sizeof(datos1[0]),compararEnteros);

  cargarArbolOrdR(&arbol2,vector,sizeof(vector[0]),0,sizeof(vector)/sizeof(vector[0])-1);

  cargarDatosOrdR(&arbol3,datos2,sizeof(datos2[0]),0,(sizeof(datos2)/sizeof(datos2[0])-1),copiarDatoVec);

  recorrerArbolEnOrden(&arbol1,mostrarEnteros,stdout);

  puts("**************************************************************");

  recorrerArbolEnOrden(&arbol2,mostrarEnteros,stdout);

  puts("**************************************************************");

  recorrerArbolEnOrden(&arbol3,mostrarEnteros,stdout);

  podarNivel(&arbol1,1);

  recorrerArbolEnOrden(&arbol1,mostrarEnteros,stdout);

  printf("\nNodos %d\n",contarNodos(&arbol1));

  printf("\nAltura nivel %d\n",alturaNivel(&arbol1));

  mayor(&arbol1,&dato,sizeof(dato));

  printf("\nMayor %d\n",dato);

  eliminarRaiz(&arbol1,&dato,sizeof(dato));

  puts("**************************************************************");

  recorrerArbolEnOrden(&arbol1,mostrarEnteros,stdout);

  vaciarArbol(&arbol1);
  vaciarArbol(&arbol2);
  vaciarArbol(&arbol3);

  return 0;
}
