#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecaEstructuras/colaEst.h"

#define PROBAR_ACOLAR
#define PROBAR_ACOLAR_
#define PROBAR_ACOLAR__

void test01(int funcion){
  ///Caso 1: Acolar y Desacolar
  ///TAM_COLA = 60
  if(funcion == 2){
    #define acolar acolar_
  }
  else if(funcion == 3){
    #define acolar acolar__
  }

  tCola cola;
  crearCola(&cola);
  int datos[] = {1,2,3,4,5},dato,i;
  int aux[] = {9,10,25,30,40,50};
  char cad[] = "Te amo Agustina Iacobaccio de mi vida!!! <3";
  char cadaux[150] = "No pudo entrar";

  acolar(&cola,cad,sizeof(cad));
  desacolar(&cola,cadaux,sizeof(cadaux));
  printf("%s\n",cadaux);

  for(i = 0 ; i < sizeof(datos)/sizeof(datos[0]) ; i++)
    acolar(&cola,&datos[i],sizeof(datos[0]));


  desacolar(&cola,&dato,sizeof(datos[0]));
  acolar(&cola,&aux[0],sizeof(datos[0]));
  desacolar(&cola,&dato,sizeof(datos[0]));
  acolar(&cola,&aux[1],sizeof(datos[0]));
  desacolar(&cola,&dato,sizeof(datos[0]));
  acolar(&cola,&aux[2],sizeof(datos[0]));
  desacolar(&cola,&dato,sizeof(datos[0]));
  acolar(&cola,&aux[3],sizeof(datos[0]));

  puts("*******************************************");
  printf("MUESTREO DE LA COLA\n");

  for(i = 0 ; i < sizeof(datos)/sizeof(datos[0]) ; i++){
    desacolar(&cola,&dato,sizeof(datos[0]));
    printf("%d\n",dato);
  }
}

void test02(int funcion){
  ///Caso 2: Corte de dato
  ///TAM_COLA = 25 -> 5+3+8+8
  ///5 h o l a \0 3 s i \0 _
  ///8 5          8 3 <- (24 usado) (1 libre)
  tCola cola;
  crearCola(&cola);
  char cad1[] = "hola";
  char cad2[] = "si";
  char cad3[] = "holas";
  char cadaux[80];
  acolar(&cola,cad1,sizeof(cad1));
  acolar(&cola,cad2,sizeof(cad2));
  desacolar(&cola,cadaux,sizeof(cadaux));
  acolar(&cola,cad3,sizeof(cad3));
  desacolar(&cola,cadaux,sizeof(cadaux));
  printf("%s\n",cadaux);
  desacolar(&cola,cadaux,sizeof(cadaux));
  printf("%s\n",cadaux);
}
void test03(int funcion){
  ///Caso 3: Corte de dato
  ///TAM_COLA = 40
  /// tam = 2 sizeof(tam) = 8
  /// 2 1 2 2 2 3 _ _ (8*3+2*3) = 30 (ocupado) + 10 (libre)
  /// _ _ 2 2 2 3 _ _ 20 (ocupado) + 10 (libre) + 10 (libre)
  tCola cola;
  crearCola(&cola);
  short int datos[] = {1,2,3},dato;
  int i,d = 25;

  for(i = 0 ; i < sizeof(datos)/sizeof(datos[0]) ; i++)
    acolar(&cola,&datos[i],sizeof(datos[0]));

  desacolar(&cola,&dato,sizeof(datos[0]));
  printf("dato desacolado %d\n",dato);
  acolar(&cola,&d,sizeof(d));
  desacolar(&cola,&dato,sizeof(datos[0]));
  printf("dato desacolado %d\n",dato);
  desacolar(&cola,&dato,sizeof(datos[0]));
  printf("dato desacolado %d\n",dato);
  ///----------------- INT -----------------
  desacolar(&cola,&i,sizeof(i));
  printf("dato desacolado %d\n",i);
}
void test04(int funcion){
  ///Caso 4: Corte de tam
  ///TAM_COLA = 38
  /// tam = 2 sizeof(tam) = 8
  /// 2 1 2 2 2 3 _  (8*3+2*3) = 30 (ocupado) + 8 (libre)
  /// _ _ 2 2 2 3 _  20 (ocupado) + 10 (libre) + 8 (libre)
  tCola cola;
  crearCola(&cola);
  short int datos[] = {1,2,3},dato;
  int i,d = 73;

  for(i = 0 ; i < sizeof(datos)/sizeof(datos[0]) ; i++)
    acolar(&cola,&datos[i],sizeof(datos[0]));

  desacolar(&cola,&dato,sizeof(datos[0]));
  printf("dato desacolado %d\n",dato);
  acolar(&cola,&d,sizeof(d));
  desacolar(&cola,&dato,sizeof(datos[0]));
  printf("dato desacolado %d\n",dato);
  desacolar(&cola,&dato,sizeof(datos[0]));
  printf("dato desacolado %d\n",dato);
  ///----------------- INT -----------------
  desacolar(&cola,&i,sizeof(i));
  printf("dato desacolado %d\n",i);
}
void test05(int funcion){
  ///Caso 5: Corte de dato y llenar cola
  ///TAM_COLA = 40
  /// tam = 2 sizeof(tam) = 8
  /// 2 1 2 2 2 3 _ _ (8*3+2*3) = 30 (ocupado) + 10 (libre)
  /// _ _ 2 2 2 3 _ _ 20 (ocupado) + 10 (libre) + 10 (libre)

  tCola cola;
  crearCola(&cola);
  short int datos[] = {1,2,3},dato;
  int i;
  char cad[] = "holaholahol";
  ///ho laholahol
  char cadaux[500];
  printf("dato en pantalla %s\n",cad);
  for(i = 0 ; i < sizeof(datos)/sizeof(datos[0]) ; i++)
    acolar(&cola,&datos[i],sizeof(datos[0]));
  desacolar(&cola,&dato,sizeof(datos[0]));
  printf("dato desacolado %d\n",dato);
  acolar(&cola,cad,sizeof(cad));
  desacolar(&cola,&dato,sizeof(datos[0]));
  printf("dato desacolado %d\n",dato);
  desacolar(&cola,&dato,sizeof(datos[0]));
  printf("dato desacolado %d\n",dato);
  ///----------------- CAD -----------------

  desacolar(&cola,cadaux,sizeof(cadaux));
  printf("dato desacolado %s\n",cadaux);
}
int main(){
  #ifdef PROBAR_ACOLAR
  puts("================================== ACOLAR Y DESACOLAR ==================================");
  test01(1);
  puts("*******************************************");
  test02(1);
  puts("*******************************************");  test03(1);
  puts("*******************************************");
  test04(1);
  puts("*******************************************");
  test05(1);
  #endif
  #ifdef PROBAR_ACOLAR_
  puts("================================= ACOLAR_ Y DESACOLAR_ =================================");
  test01(2);
  puts("*******************************************");
  test02(2);
  puts("*******************************************");
  test03(2);
  puts("*******************************************");
  test04(2);
  puts("*******************************************");
  test05(2);
  #endif
  #ifdef PROBAR_ACOLAR__
  puts("================================ ACOLAR__ Y DESACOLAR__ ================================");
  test01(3);
  puts("*******************************************");
  test02(3);
  puts("*******************************************");
  test03(3);
  puts("*******************************************");
  test04(3);
  puts("*******************************************");
  test05(3);
  #endif
  return 0;
}
