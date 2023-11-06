#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TP.h"

int compararNumeroDeSocio(const void* a, const void* b){
  tSocio* pa = (tSocio*)a;
  tSocio* pb = (tSocio*)b;
  return pa->nro-pb->nro;
}

int compararRegistroIndiceSocios(const void* elem1, const void*elem2){
    tRegistroIndice* regIndice1 = (tRegistroIndice*)elem1;
    tRegistroIndice* regIndice2 = (tRegistroIndice*)elem2;

    long int *clave1 = (long int *)(regIndice1->clave);
    long int *clave2 = (long int *)(regIndice2->clave);

    return *clave1 - *clave2;
}

void mostrarNroReg(const void* a, FILE* pf){
  tRegistroIndice *pa = (tRegistroIndice *)a;
  long int* clave = (long int*)pa->clave;
  fprintf(pf,"Numero de registro: %d Numero de socio: %ld\n",pa->nroReg,*clave);
}

tLista siguienteDeLista(tLista* pl){
  if(*pl == NULL)
    return 0;
  if((*pl)->sig){
    pl = &(*pl)->sig;
    return *pl;
  }
  return 0;
}

int acumular(){
  return 1;
}

int main(){
  ///char op;
  ///char ruta[150];
  FILE *bin;
  tIndice indice;
  tSocio socio;

  unsigned iteraciones = 0;

  ///crearLoteDePrueba();

  ///printf("Ingrese la ruta:");
  ///scanf("%s",ruta);

  ///socios.txt es la ruta correcta

  if(pasarArchTxtABin("socios.txt","socios.data") != TODO_OK)
    return 0;

  crearIndice(&indice,sizeof(long int),compararRegistroIndiceSocios);

  abrirArchivo(&bin,"socios.data","rb");

  fread(&socio,sizeof(tSocio),1,bin);

  while(!feof(bin)){

    insertarIndice(&indice,&socio.nro,iteraciones++);

    fread(&socio,sizeof(tSocio),1,bin);

  }

  mostrarIndice(&indice,mostrarNroReg,stdout);

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






