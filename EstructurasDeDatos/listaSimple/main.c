#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecaEstructuras/lista.h"

typedef struct{
  int codProd;
  int stock;
}tProducto;

typedef struct{
  char nya[51];
  int edad;
  float nota;
}tAlumno;

void mostrarEnteros(const void* a,FILE* pf){
  int* pa = (int*)a;
  fprintf(pf,"%d ",*pa );
}

int compararEnteros(const void*a, const void*b){
  int* pa = (int*)a;
  int* pb = (int*)b;
  return *pa-*pb;
}

int acumularEnteros(void** pl,size_t* pltam,const void* dato,size_t tam){
  return 1;
}

int acumularStock(void* a,const void* b){
  tProducto* pa = (tProducto*)a;
  tProducto* pb = (tProducto*)b;
  pa->stock += pb->stock;
  return 1;
}

int compararCodProd(const void*a, const void*b){
  tProducto* pa = (tProducto*)a;
  tProducto* pb = (tProducto*)b;
  return pa->codProd-pb->codProd;
}

void mostrarProductos(const void* a, FILE* pf){
  tProducto* pa = (tProducto*)a;
  fprintf(pf,"Codigo de Producto %d | Stock %d\n",pa->codProd,
                                              pa->stock);
}

void acumularNotas(void* a, const void* b){
  float* pa = (float*)a;
  tAlumno* pb = (tAlumno*)b;
  *pa += pb->nota;
}

int compararNotas(const void*a, const void*b){
  tAlumno* pa = (tAlumno*)a;
  float* pb = (float*)b;
  if (pa->nota-*pb == 0)
    return 0;
  return pa->nota-*pb - 1;
}

void mostrarAlumnos(const void* a,FILE* pf){
  tAlumno* pa = (tAlumno*)a;
  fprintf(pf,"%s %d %.2f\n",pa->nya,
                            pa->edad,
                            pa->nota);
}

void test01(){
  int list[] = {5,2,9},i,dato;
  tLista lista;
  crearLista(&lista);
  /*
  for(i = 0 ; i < sizeof(list)/sizeof(list[0]) ; i++)
    ponerAlComienzo(&lista,&list[i],sizeof(list[0]));
  */
  for(i = 0 ; i < sizeof(list)/sizeof(list[0]) ; i++)
    ponerEnOrden(&lista,&list[i],sizeof(list[0]),compararEnteros,acumularEnteros);
  /*
  for(i = 0 ; i < sizeof(list)/sizeof(list[0]) ; i++){
    sacarPrimeroLista(&lista,&dato,sizeof(list[0]));
    printf("%d ",dato);
  }
  */
  //ordenarLista(&lista,compararEnteros);
  mostrarLista(&lista,mostrarEnteros,stdout);
  puts(" ");
  mostrarListaAlReves(&lista,mostrarEnteros,stdout);
  puts(" ");
  mostrarListaYVaciar(&lista,mostrarEnteros,stdout);
  puts(" ");
  mostrarListaAlRevesYVaciar(&lista,mostrarEnteros,stdout);
}

void test02(){
  tProducto producto[] = {
                          {8,-1},
                          {1,2000},
                          {6,-1},
                          {6,1},
                          {6,5},
                          {6,10},
                          {8,5},
                          {3,2},
                          {6,5},
                          {3,15},
                          {3,20},
                          {2,25},
                          {1,-20},
                          {1,150},
                         };
  int i;
  tLista lista;

  crearLista(&lista);

  for(i = 0 ; i < sizeof(producto)/sizeof(producto[0]) ; i++)
    ponerAlComienzo(&lista,&producto[i],sizeof(producto[0]));

  agrupar(&lista,compararCodProd,acumularStock);
  mostrarLista(&lista,mostrarProductos,stdout);
}

void test03(){
  tProducto producto[] = {
                          {8,-1},
                          {1,2000},
                          {6,-1},
                          {6,1},
                          {6,5},
                          {6,10},
                          {8,5},
                          {3,2},
                          {6,5},
                          {3,15},
                          {3,20},
                          {2,25},
                          {1,-20},
                          {1,150},
                         };
  int i;
  tProducto datos[] = {
                      {1,0},
                      {2,0},
                      {3,0},
                      {6,0},
                      {8,0},
                     };
  tLista lista;

  crearLista(&lista);

  for(i = 0 ; i < sizeof(producto)/sizeof(producto[0]) ; i++)
    ponerAlComienzo(&lista,&producto[i],sizeof(producto[0]));

  for(i = 0 ; i < sizeof(datos)/sizeof(datos[0])-1 ; i++)
    eliminarPorClave(&lista,&datos[i],compararCodProd);

  agrupar(&lista,compararCodProd,acumularStock);
  mostrarLista(&lista,mostrarProductos,stdout);
}

void test04(){
  tAlumno list[] = {
                    {"Fgustina Iacobaccio <3",20,7},
                    {"Egustina Iacobaccio <3",20,8},
                    {"Dgustina Iacobaccio <3",20,9},
                    {"Cgustina Iacobaccio <3",20,8},
                    {"Bgustina Iacobaccio <3",20,9.5},
                    {"Agustina Iacobaccio <3",20,10},
                   };
  int i;
  float notas = 0;
  float nota = 10;
  tLista lista;
  crearLista(&lista);

  for(i = 0 ; i < sizeof(list)/sizeof(list[0]) ; i++)
    ponerAlComienzo(&lista,&list[i],sizeof(list[0]));

  mostrarLista(&lista,mostrarAlumnos,stdout);
  reduceList(&lista,&notas,acumularNotas);
  printf("Promedio de notas es %.2f\n",notas/(sizeof(list)/sizeof(list[0])));
  printf("Las notas deben ser mayores o iguales a %.2f\nLos nodos eliminados fueron %d\n",nota,filterList(&lista,&nota,compararNotas));
  mostrarLista(&lista,mostrarAlumnos,stdout);
}

int main(){
  //test01();
  //test02();
  //test03();
  test04();

  return 0;
}
