#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../../EstructurasDeDatos/bibliotecaEstructuras/colaDin.h"

#define PROBAR_ESTATICA

#ifdef PROBAR_ESTATICA

#include "../../EstructurasDeDatos/bibliotecaEstructuras/colaEst.h"

#define tCola t_cola
#define crearCola crear_cola
#define acolar a_colar
#define desacolar des_acolar
#define verPrimeroCola ver_primero_cola
#define colaVacia cola_vacia

#endif // PROBAR_ESTATICA

#define ITERACIONES 5000

///Ejercicio 3.5
///
///Resuelva la simulación de la cola de espera en un
///cajero automático.
///Suponga que cada cliente
///demora en el mismo un tiempo aleatorio de 1, 3 ó, 5
///minutos con igual probabilidad, y que los
///clientes llegan al mismo de a uno, con
///intervalo de arribo aleatorio de 1, 5 ó 9 minutos,
///con igual
///probabilidad.
///La simulación termina después que la cola
///queda vacía cinco veces.

int main(){

  int demora[] = {1,3,5};
  int arribo[] = {1,5,9};
  int col_vacia = 0;
  int num_cliente = 1;
  int salio;
  int llego;
  int cliente;
  tCola cola;
  time_t t;
  int iter = 0;

  while(iter++ < ITERACIONES){

    srand((unsigned) time(&t));

    while(col_vacia < 5){

      crearCola(&cola);
      cliente = demora[rand()%3];
      acolar(&cola,&cliente,sizeof(cliente));
      salio = cliente;
      llego = arribo[rand()%3];

      while(!colaVacia(&cola)){

        if(salio == 0){

          desacolar(&cola,&cliente,sizeof(cliente));
          printf("El cliente [%d] se demoro %d minutos\n",num_cliente++,cliente);

          if(!colaVacia(&cola))
            verPrimeroCola(&cola,&salio,sizeof(cliente));
        }

        if(!colaVacia(&cola) && llego == 0){

          cliente = demora[rand()%3];
          llego = arribo[rand()%3];
          acolar(&cola,&cliente,sizeof(cliente));

        }

        llego--;
        salio--;

      }
      printf("Se vacio la cola\n");
      col_vacia++;
    }
    col_vacia = 0;

  }

  return 0;
}
