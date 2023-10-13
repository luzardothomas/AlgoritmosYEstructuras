#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecaEstructuras/listaDoble.h"

typedef struct{
  int codProd;
  int stock;
}tProducto;


void mostrarEnteros(const void* a){
  int* pa = (int*)a;
  printf("%d ",*pa);
}

int compararEnteros(const void* a, const void* b){
  int* pa = (int*)a;
  int* pb = (int*)b;
  return *pa-*pb;
}

void mostrarProductos(const void* a){
  tProducto* pa = (tProducto*)a;
  printf("CodProd %d Stock %d\n",pa->codProd,
                                 pa->stock);
}

int compararCodProd(const void* a, const void* b){
  tProducto* pa = (tProducto*)a;
  tProducto* pb = (tProducto*)b;
  return pa->codProd-pb->codProd;
}

int compararStock(const void* a, const void* b){
  tProducto* pa = (tProducto*)a;
  int* pb = (int*)b;
  return pa->stock-*pb;
}

int acumularStock(void* a, const void* b){
  tProducto* pa = (tProducto*)a;
  tProducto* pb = (tProducto*)b;
  return pa->stock += pb->stock;
}

void test01(){
  int datos[] = {3,1,99,150,2,0,8,5,999};
  int i;
  tLista lista;
  crearLista(&lista);
  /*
  for(i = 0 ; i < sizeof(datos)/sizeof(datos[0]) ; i++)
    ponerAlComienzo(&lista,&datos[i],sizeof(datos[0]));
  */
  for(i = 0 ; i < sizeof(datos)/sizeof(datos[0]) ; i++)
    ponerEnOrden(&lista,&datos[i],sizeof(datos[0]),compararEnteros);
  //ordenarLista(&lista,compararEnteros);
  mostrarDeIzquierdaADerecha(&lista,mostrarEnteros);

  /// ===================================================
  puts("\n===============================================");

  //ordenarLista(&lista,compararEnteros);
  mostrarDeDerechaAIzquierda(&lista,mostrarEnteros);
}

void test02(){
  tProducto datos[] = {
                        {7,80},
                        {7,1},
                        {6,56},
                        {8,55},
                        {3,25},
                        {6,50},
                        {3,15},
                        {3,15},
                        {7,80},
                      };
  int i;
  int stock = 49;
  tProducto cantStock = {0,0};
  int productos;
  tLista lista;
  crearLista(&lista);

  for(i = 0 ; i < sizeof(datos)/sizeof(datos[0]) ; i++)
    ponerAlComienzo(&lista,&datos[i],sizeof(datos[0]));

  printf("Esta la lista vacia %d\n",listaVacia(&lista));
  vaciarLista(&lista);
  printf("Esta la lista vacia %d\n",listaVacia(&lista));

  for(i = 0 ; i < sizeof(datos)/sizeof(datos[0]) ; i++)
    ponerAlComienzo(&lista,&datos[i],sizeof(datos[0]));

  printf("Esta la lista vacia %d\n",listaVacia(&lista));
  /*
  ordenarLista(&lista,compararCodProd);
  mostrarDeIzquierdaADerecha(&lista,mostrarProductos);
  puts("**************************************************************************************************");
  */


  ///puts("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
  ///productos = reduce(&lista,&cantStock,acumularStock);
  ///printf("El promedio de stock de los %d productos es de %.2f\n",productos,cantStock.stock/(float)productos);
  ///puts("--------------------------------------------------------------------------------------------------");
  ///puts("Productos filtrados mayores de 100 unidades por stock");
  /*
  printf("Los nodos eliminados tras filtrarse han sido %d\n",filter(&lista,&stock,compararStock));
  mostrarDeIzquierdaADerecha(&lista,mostrarProductos);
  puts("==================================================================================================");
  mostrarDeDerechaAIzquierda(&lista,mostrarProductos);

  */
  puts("==================================================================================================");
  agrupar(&lista,compararCodProd,acumularStock);
  mostrarDeIzquierdaADerecha(&lista,mostrarProductos);
  puts("==================================================================================================");
  mostrarDeDerechaAIzquierda(&lista,mostrarProductos);
}

void test03(){
  tProducto datos[] = {
                        {6,-2},
                        {8,5},
                        {3,2},
                        {6,5},
                        {3,1},
                        {3,150},
                      };
  int i;
  int stock = 3;
  tLista lista;
  crearLista(&lista);

  for(i = 0 ; i < sizeof(datos)/sizeof(datos[0]) ; i++)
    ponerAlComienzo(&lista,&datos[i],sizeof(datos[0]));

  agrupar(&lista,compararCodProd,acumularStock);
  mostrarDeIzquierdaADerecha(&lista,mostrarProductos);
  puts("==================================================================================================");
  mostrarDeDerechaAIzquierda(&lista,mostrarProductos);
  printf("Los nodos eliminados han sido %d con el dato %d\n",eliminarPorClave(&lista,&stock,compararStock),stock);
  mostrarDeIzquierdaADerecha(&lista,mostrarProductos);
  puts("==================================================================================================");
  mostrarDeDerechaAIzquierda(&lista,mostrarProductos);
}

int main(){
  puts("==================================== TEST 1 ====================================");
  test01();
  //printf("\n");
  //puts("==================================== TEST 2 ====================================");  //test02();
  //puts("==================================== TEST 3 ====================================");
  //test03();
  return 0;
}
