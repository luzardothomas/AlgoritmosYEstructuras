#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TP.h"
#include <time.h>

int compararNumeroDeSocio(const void* a, const void* b){
  tSocio* pa = (tSocio*)a;
  tSocio* pb = (tSocio*)b;
  return pa->nro-pb->nro;
}
int compararRegistroIndiceSocios(const void* a, const void* b){
  long int* pa = (long int*)a;
  long int* pb = (long int*)b;

  return *pa-*pb;
}
void mostrarNroSocio(const void * a, unsigned b, void * c){
  long int* nroSocio = (long int*)a;

  printf("Numero de registro %d Numero de socio %ld\n",b,*nroSocio);
}
int main(){
  int op;
  char ruta[150];
  unsigned iteraciones = 0;
  FILE *bin;

  tIndice indiceNroSocio;
  tSocio socio;
  int limpiar[] = {1,1,0,1,0,0};
  fOpcion opciones[] = {darDeAlta,
                        darDeBaja,
                        listarSociosDeBaja,
                        modificarAyN,
                        verMayoresDeudores,
                        verSociosActivos,
                       };

  ///A = 0
  ///B = 1
  ///L = 2
  ///M = 3
  ///P = 4
  ///V = 5

  ///crearLoteDePrueba();

  printf("Ingrese la ruta:");
  scanf("%s",ruta);

  limpiarBuffer();

  ///socios.txt es la ruta correcta

  if(pasarArchTxtABin(ruta,"socios.data") != TODO_OK)
    return RUTA_INVALIDA;

  crearIndice(&indiceNroSocio,sizeof(long int),compararRegistroIndiceSocios);

  abrirArchivo(&bin,"socios.data","r+b");

  fread(&socio,sizeof(tSocio),1,bin);

  ///Llenar el Índice

  while(!feof(bin)){
    if(A_MAYUS(socio.estado) == 'A')
      insertarIndice(&indiceNroSocio,&socio.nro,iteraciones);

    iteraciones++;
    fread(&socio,sizeof(tSocio),1,bin);
  }

  ///Volvemos al comienzo del Archivo

  rewind(bin);

  ///Loop principal de Menu para nuevos socios

  op = menu();

  while(op){

    opciones[op-1](&indiceNroSocio,&iteraciones,bin);

    if(limpiar[op-1])
      limpiarBuffer();

    op = menu();

    limpiarPantalla();

  }

  puts("============================================== PRE CARGA INDICE ==============================================");

  recorrerIndice(&indiceNroSocio,mostrarNroSocio,stdout);

  ///Grabamos el Archivo Índice

  grabarIndice(&indiceNroSocio,"socios.idx");

  ///Liberamos la memoria del Índice

  vaciarIndice(&indiceNroSocio);

  /**================================================= TESTEO =================================================
    -Creo el Índice
    -Lo cargo
    -Lo recorro
    -Leo el socios.data
  */

  crearIndice(&indiceNroSocio,sizeof(long int),compararRegistroIndiceSocios);
  cargarIndice(&indiceNroSocio,"socios.idx");

  puts("============================================== POST CARGA INDICE ==============================================");

  recorrerIndice(&indiceNroSocio,mostrarNroSocio,stdout);

  puts("============================================== TODOS LOS SOCIOS ==============================================");

  ///Mostrar todos los Socios (Activos/Inactivos)

  rewind(bin);

  fread(&socio,sizeof(tSocio),1,bin);

  while(!feof(bin)){
    mostrarSocios(&socio,stdout);
    fread(&socio,sizeof(tSocio),1,bin);
  }

  vaciarIndice(&indiceNroSocio);
  fclose(bin);
  return 0;
}
