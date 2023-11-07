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

int compararRegistroIndiceSocios(const void* elem1, const void*elem2){
  tRegistroIndice* regIndice1 = (tRegistroIndice*)elem1;
  tRegistroIndice* regIndice2 = (tRegistroIndice*)elem2;

  long int *clave1 = (long int *)(regIndice1->clave);
  long int *clave2 = (long int *)(regIndice2->clave);

  return *clave1 - *clave2;
}

void mostrarNroSocio(const void *a, unsigned b, void *c){
  FILE* pf = (FILE*)c;
  tRegistroIndice *pa = (tRegistroIndice *)a;
  long int* clave = (long int*)pa->clave;
  fprintf(pf,"Numero de registro: %d Numero de socio: %ld\n",pa->nroReg,*clave);
}

void mostrarDniSocio(const void *a, unsigned b, void *c){
  FILE* pf = (FILE*)c;
  tRegistroIndice *pa = (tRegistroIndice *)a;
  long int* clave = (long int*)pa->clave;
  fprintf(pf,"Numero de registro: %d Dni de socio: %ld\n",pa->nroReg,*clave);
}

int main(){
  int op;
  char ruta[150];
  unsigned iteraciones = 0;
  FILE *bin;
  FILE *idx;
  FILE *act;
  tIndice indiceNroSocio;
  tIndice indiceDniSocio;
  tRegistroIndice dato;
  tSocio socio;
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

  ///printf("Ingrese la ruta:");
  ///scanf("%s",ruta);

  ///socios.txt es la ruta correcta

  strcpy(ruta,"socios.txt");

  if(pasarArchTxtABin(ruta,"socios.data") != TODO_OK)
    return 0;

  crearIndice(&indiceNroSocio,sizeof(long int),compararRegistroIndiceSocios);
  crearIndice(&indiceDniSocio,sizeof(long int),compararRegistroIndiceSocios);

  abrirArchivo(&bin,"socios.data","rb");

  fread(&socio,sizeof(tSocio),1,bin);

  while(!feof(bin)){

    insertarIndice(&indiceNroSocio,&socio.nro,iteraciones);
    insertarIndice(&indiceDniSocio,&socio.dni,iteraciones);

    iteraciones++;

    fread(&socio,sizeof(tSocio),1,bin);

  }

  ///Volvemos al comienzo del Archivo

  rewind(bin);

  ///Loop principal de Menu para nuevos socios

  op = menu();

  while(op){

    opciones[op-1](&indiceNroSocio,iteraciones,bin);

    op = menu();
  }

  puts("");

  limpiarPantalla();

  ///========================================= TEST DE PRIMITIVAS =========================================

  long int n = 20;

  while(n){
    recorrerIndice(&indiceNroSocio,mostrarNroSocio,stdout);
    socio.nro = n;
    memcpy(&dato.clave,&socio.nro,sizeof(socio.nro));
    if(buscarIndice(&indiceNroSocio,&dato,dato.nroReg)){
      printf("\nNumero de registro %d\n",dato.nroReg);
      printf("\nNro de socio:%ld\n",*(long int*)dato.clave);
    }
    n--;
  }

  puts("");

  n = 20;

  /**
  while(n){
    recorrerIndice(&indiceNroSocio,mostrarNroSocio,stdout);
    socio.nro = n;
    memcpy(&dato.clave,&socio.nro,sizeof(socio.nro));
    if(eliminarIndice(&indiceNroSocio,&dato,dato.nroReg)){
      printf("\nNumero de registro %d\n",dato.nroReg);
      printf("\nNro de socio:%ld\n",*(long int*)dato.clave);
    }
    n--;
  }

  puts("=======================================================================================");
  */

  recorrerIndice(&indiceNroSocio,mostrarNroSocio,stdout);

  ///Grabamos el Archivo Índice
  grabarIndice(&indiceNroSocio,"socios.idx");


  ///Liberamos la memoria del Índice

  vaciarIndice(&indiceNroSocio);
  fclose(bin);

  ///========================================= TESTING =========================================

  abrirArchivo(&bin,"socios.data","r+b");
  abrirArchivo(&act,"socios_act.data","wb");
  abrirArchivo(&idx,"socios.idx","rb");

  ///Actualizamos el Archivo de Socios utilizando el Archivo Índice

  ///Leemos el Archivo del Índice y movemos el cabezal con el
  ///tamaño del socio multiplicando al número de registro, y
  ///ese sería nuestro desplazamiento en socios.data

  fread(&dato,sizeof(tRegistroIndice),1,idx);
  fseek(bin,sizeof(tSocio)*dato.nroReg,SEEK_SET);

  while(!feof(idx)){

    fread(&socio,sizeof(tSocio),1,bin);
    fwrite(&socio,sizeof(tSocio),1,act);

    ///Repetimos el proceso

    fread(&dato,sizeof(tRegistroIndice),1,idx);
    fseek(bin,sizeof(tSocio)*dato.nroReg,SEEK_SET);
  }

  remove("socios.data");
  rename("socios_act.data","socios.data");

  fclose(bin);
  fclose(idx);
  fclose(act);
  return 0;

}
