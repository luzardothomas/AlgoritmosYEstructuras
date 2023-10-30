#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TP.h"

typedef struct{
  long int numSocio;
  unsigned numReg;
}tRegistro;

int compararNumeroDeSocio(const void* a, const void* b){
  tSocio* pa = (tSocio*)a;
  tSocio* pb = (tSocio*)b;
  return pa->nro-pb->nro;
}

void mostrarNumReg(const void* a){
  unsigned *pa = (unsigned *)a;
  printf("%ld\n",*pa);
}

int main(){
  char op;
  char ruta[150];
  FILE *bin;
  tIndice indice;
  tLista listaSocios;
  tSocio socio;
  tRegistro registro;
  unsigned i = 0;
  int iteraciones;

  //crearLoteDePrueba();

  ///printf("Ingrese la ruta:");
  ///scanf("%s",ruta);

  ///socios.txt es la ruta correcta

  if(pasarArchTxtABin("socios.txt","socios.data") != TODO_OK)
    return 0;

  abrirArchivo(&bin,"socios.data","rb");

  crearIndice(&indice);

  fread(&socio,sizeof(tSocio),1,bin);

  iteraciones = ftell(&bin);

  while(!feof(bin)){
    ponerEnOrden(&listaSocios,&socio,sizeof(tSocio),compararNumeroDeSocio,NULL);
    fread(&socio,sizeof(tSocio),1,bin);
  }

  while(sacarPrimeroLista(&listaSocios,&socio,sizeof(tSocio))){
    insertarIndice(&indice,&socio,i++);
  }
  mostrarIndice(&indice,mostrarNumReg);

  ///En lugar de un switch case se podría
  ///usar una variable que contenga funciones
  ///de acciones a concretar.

  ///fAccion[] = {
///                Alta, A
///                Baja, B
///                ListarBajas, L
///                Modificar, M
///                PagoRetrasado, P
///                VerSocios, V
///              };

  ///while(op){
  /// Utilizamos el fAccion[op-1]
  /// op = menu();
  ///}

  fclose(bin);
  return 0;

}






