#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionesclase04.h"

int main(){

  /*tStock vec[]={
                  {"mart",1,10},
                  {"dest",2,20},
                  {"tornillos",50,5},
                  {"clavos",100,5},
                  {"taladro",1,95},
                  {"lampara",1,15},
                  {"pegamento",1,30},
                  {"podadora",1,80},
                  {"sierra",1,100},
                };
  FILE* pf = fopen("loteStock.dat", "wb");

  fwrite(vec,sizeof(vec),1,pf);

  fclose(pf);*/

  tCola pedido;
  tPedido ped;
  tPedido atendido;
  tStock stock;

  int nro_ped;
  int total_vendido = 0;

  FILE* pError, *pPed, *pMay, *pMen, *pStock;

  pError = fopen("error.dat", "wb");
  pPed = fopen("lotePedido.dat","rb");
  pStock = fopen("loteStock.dat","r+b");
  pMay = fopen("mayor100.dat","wb");
  pMen = fopen("menor100.dat","wb");

  crearCola(&pedido);


  ///¿Qué se pidió?
  puts("=================== PEDIDOS ===================");
  fread(&ped,sizeof(tPedido),1,pPed);
  while(!feof(pPed)){
    printf("Numero pedido %d|||Cantidad %d|Codigo %s| Precio %.2f\n",ped.nro_ped,ped.cant,ped.cod,ped.precio);
    fread(&ped,sizeof(tPedido),1,pPed);
  }
  ///¿Qué hay en stock?
  puts("=================== STOCK ===================");
  fread(&stock,sizeof(tStock),1,pStock);
  while(!feof(pStock)){
    printf("Codigo %s|||Cantidad %d|| Precio %.2f\n",stock.cod,stock.cant,stock.precio);
    fread(&stock,sizeof(tStock),1,pStock);
  }
  ///Reseteo los punteros a FILE
  rewind(pPed);
  rewind(pStock);

  fread(&ped,sizeof(tPedido),1,pPed);
  nro_ped = ped.nro_ped;
  fseek(pPed,-1*sizeof(tPedido),SEEK_CUR);

  while(!feof(pPed)){

    while(fread(&ped,sizeof(tPedido),1,pPed) && ped.nro_ped == nro_ped){

      ///Busco si existe el producto en el Stock
      fread(&stock,sizeof(tStock),1,pStock);

      while(!feof(pStock) && strcmp(stock.cod,ped.cod) != 0)
        fread(&stock,sizeof(tStock),1,pStock);

      ///Vacio el buffer para actualizar el stock
      fflush(pStock);

      ///Si la cantidad stock es mayor o igual a la cantidad pedida y el codigo es igual
      if(stock.cant >= ped.cant && strcmp(stock.cod,ped.cod) == 0){

        ///Pongo en cola el pedido
        acolar(&pedido,&ped,sizeof(tPedido));

        ///Cuento lo vendido
        total_vendido += ped.cant*ped.precio;

        ///Actualizo stock
        stock.cant -= ped.cant;
        fwrite(&stock,sizeof(tStock),1,pStock);
      }
      else if(stock.cant < ped.cant)
        fprintf(pError,"Error: Stock insuficiente\n");
      else
        fprintf(pError,"Error: Ese dato no fue encontrado en el stock\n");

      ///Reseteo el puntero Stock
      rewind(pStock);
    }

    ///Reseteo el puntero a file para el dato con el que cortó
    if(ped.nro_ped != nro_ped)
      fseek(pPed,-1*sizeof(tPedido),SEEK_CUR);


    ///Actualizo el comparador al salir
    nro_ped = ped.nro_ped;

    ///Agrupar por ventas > 100 y < 100
    while(desacolar(&pedido,&atendido,sizeof(tPedido))){
      if(total_vendido >= 100)
        fwrite(&atendido,sizeof(tPedido),1,pMay);
      else
        fwrite(&atendido,sizeof(tPedido),1,pMen);
    }

    ///Reseteo el total vendido
    total_vendido = 0;
  }

  fclose(pPed);
  fclose(pError);
  fclose(pMay);
  fclose(pMen);
  return 0;
}
