#include "TP.h"

#ifdef _WIN32
  #include<windows.h>
#endif

void limpiarPantalla(){
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

int crearLoteDePrueba(){

  tSocio socios[]  = {
                       {1,"Luzardo Thomas",42597231,{27,1,2001},'M',{1,1,2023},"ADULTO",{5,10,2023},'I',{5,10,2023}},
                       {2,"Luzardo Ahomas",52597231,{27,1,2001},'M',{1,1,2023},"ADULTO",{5,10,2023},'I',{5,10,2023}},
                       {3,"Luzardo Bhomas",62597231,{27,1,2001},'M',{1,1,2023},"ADULTO",{5,10,2023},'I',{5,10,2023}},
                       {4,"Luzardo Chomas",62597231,{27,1,2001},'M',{1,1,2023},"ADULTO",{5,10,2023},'A',{5,10,2023}},
                     };
  FILE* pf,*pError;
  int i;

  pf = fopen("socios.txt","wt");
  pError = fopen("error.txt","wt");

  if(pf == NULL || pError == NULL)
    return ERROR_ARCH;

  for(i = 0 ; i < sizeof(socios)/sizeof(socios[0]) ; i++){

      if(validarLoteDeDatosDelClub(&socios[i]) == 1){

      fprintf(pf,"%ld|%s|%ld|%d/%d/%d|%c|%d/%d/%d|%s|%d/%d/%d|%c|%d/%d/%d\n",socios[i].nro,
                                                                             socios[i].nya,
                                                                             socios[i].dni,
                                                                             socios[i].nacimiento.dia,
                                                                             socios[i].nacimiento.mes,
                                                                             socios[i].nacimiento.anio,
                                                                             socios[i].sexo,
                                                                             socios[i].afiliacion.dia,
                                                                             socios[i].afiliacion.mes,
                                                                             socios[i].afiliacion.anio,
                                                                             socios[i].categoria,
                                                                             socios[i].ultimaPaga.dia,
                                                                             socios[i].ultimaPaga.mes,
                                                                             socios[i].ultimaPaga.anio,
                                                                             socios[i].estado,
                                                                             socios[i].baja.dia,
                                                                             socios[i].baja.mes,
                                                                             socios[i].baja.anio
                                                                             );

      }
      else{

        printf("Se produjo uno o varios errores al cargar el lote de datos, consultar en error.txt\r");
        fprintf(pError,"NUM_SOCIO:%ld|DNI:%ld\n",socios[i].nro,socios[i].dni);

      }
  }

  fclose(pError);
  fclose(pf);

  return TODO_OK;

}

int validarLoteDeDatosDelClub(tSocio* socio){

  if(!(socio->nro >= 1 && socio->nro <= 10000000))
    return ERROR_REGIS;

  if(!(socio->dni >= 10000 && socio->dni <= 100000000))
    return ERROR_REGIS;

  if(!(socio->sexo == 'F' || socio->sexo == 'M' || socio->sexo == 'O'))
    return ERROR_REGIS;

  if(!((strcmp(socio->categoria,"MENOR") == 0)    ||
      (strcmp(socio->categoria,"CADETE") == 0)    ||
      (strcmp(socio->categoria,"ADULTO") == 0)    ||
      (strcmp(socio->categoria,"VITALICIO") == 0) ||
      (strcmp(socio->categoria,"HONORARIO") == 0) ||
      (strcmp(socio->categoria,"JUBILADO") == 0)))
    return ERROR_REGIS;

  if(!(socio->estado == 'A' || socio->estado == 'I'))
    return ERROR_REGIS;

  if(socio->estado == 'A'){
    socio->baja.dia = 0;
    socio->baja.mes = 0;
    socio->baja.anio = 0;
  }

  return TODO_OK;

}

int pasarArchTxtABin(const char* rutaTxt,const char* rutaBin){

  FILE *pf;
  FILE *bin;

  tSocio socios;

  abrirArchivo(&pf,rutaTxt,"rt");
  abrirArchivo(&bin,rutaBin,"wb");

  if(pf == NULL || bin == NULL)
    return ERROR_ARCH;

  printf("LISTADO DE SOCIOS:\n");

  while(leerSocios(&pf,&socios) > 0){

    mostrarSocios(&socios,stdout);
    grabarSocios(&bin,&socios);

  }

  fclose(pf);
  fclose(bin);

  return TODO_OK;
}

int abrirArchivo(FILE** pf, const char* ruta, const char* modo){

  *pf = fopen(ruta,modo);

  if(*pf == NULL)
    return ERROR_ARCH;

  return TODO_OK;

}

int leerSocios(FILE** pf,tSocio* socios){

  return fscanf(*pf,"%ld|%[^|]|%ld|%u/%u/%u|%c|%u/%u/%u|%[^|]|%u/%u/%u|%c|%u/%u/%u\n",&socios->nro,
                                                                                      socios->nya,
                                                                                      &socios->dni,
                                                                                      &socios->nacimiento.dia,
                                                                                      &socios->nacimiento.mes,
                                                                                      &socios->nacimiento.anio,
                                                                                      &socios->sexo,
                                                                                      &socios->afiliacion.dia,
                                                                                      &socios->afiliacion.mes,
                                                                                      &socios->afiliacion.anio,
                                                                                      socios->categoria,
                                                                                      &socios->ultimaPaga.dia,
                                                                                      &socios->ultimaPaga.mes,
                                                                                      &socios->ultimaPaga.anio,
                                                                                      &socios->estado,
                                                                                      &socios->baja.dia,
                                                                                      &socios->baja.mes,
                                                                                      &socios->baja.anio
                                                                                      );

}

void mostrarSocios(const tSocio* socios, FILE* pf){

  fprintf(pf,"%ld|%s|%ld|%d/%d/%d|%c|%d/%d/%d|%s|%d/%d/%d|%c|%d/%d/%d\n",socios->nro,
                                                                         socios->nya,
                                                                         socios->dni,
                                                                         socios->nacimiento.dia,
                                                                         socios->nacimiento.mes,
                                                                         socios->nacimiento.anio,
                                                                         socios->sexo,
                                                                         socios->afiliacion.dia,
                                                                         socios->afiliacion.mes,
                                                                         socios->afiliacion.anio,
                                                                         socios->categoria,
                                                                         socios->ultimaPaga.dia,
                                                                         socios->ultimaPaga.mes,
                                                                         socios->ultimaPaga.anio,
                                                                         socios->estado,
                                                                         socios->baja.dia,
                                                                         socios->baja.mes,
                                                                         socios->baja.anio
                                                                         );
}

void grabarSocios(FILE** pf, tSocio* socios){

  fwrite(socios,sizeof(tSocio),1,*pf);

}

char menu(){

  char op;
  char abc[] = {
                 1 , 2, 'C',
                'D','E','F',
                'G','H','I',
                'J','K', 3 ,
                 4, 'N','O',
                 5,'Q','R' ,
                 0,'T','U' ,
                 6,'W','X' ,
                   'Y','Z'
               };

  limpiarPantalla();
  mostrarMenu();
  fflush(stdin);
  scanf("%c",&op);

  if(ES_LETRA(op)){
      op = A_MAYUS(op);
      op -= 65;
  }
  else
    op = 3;

  ///S = 0

  ///A = 1
  ///B = 2
  ///L = 3
  ///M = 4
  ///P = 5
  ///V = 6

  while(abc[op] > 7){

    limpiarPantalla();
    printf("OPCION NO VALIDA\n\n");
    mostrarMenu();
    fflush(stdin);
    scanf("%c",&op);

    if(ES_LETRA(op)){
      op = A_MAYUS(op);
      op -= 65;
    }
    else
      op = 3;

  }

  op = abc[op];

  return op;

}

void mostrarMenu(){

  printf("MENU:\n");
  printf("A-->DAR DE ALTA UN SOCIO\n"
         "M-->MODIFICAR APELLIDO,NOMBRE\n"
         "B-->DAR DE BAJA UN SOCIO\n"
         "L-->LISTAR SOCIOS DADOS DE BAJA\n"
         "V-->LISTAR SOCIOS DADOS DE ALTA\n"
         "P-->TOP 10 CON MAYOR RETRASO EN LA CUOTA\n"
         "S-->SALIR\n");
  printf("Ingrese la opcion deseada-->\t");
}
