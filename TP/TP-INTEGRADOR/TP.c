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
                       {1, "Iacobaccio, Agustina",44263896, {16, 1, 2003}, 'F', {2, 3, 2022}, "ADULTO", {9, 9, 2023}, 'A', {5, 11, 2023}},
                       {2, "Luzardo, Gaston Thomas", 42597231, {27, 1, 2001}, 'M', {1, 1, 2023}, "ADULTO", {5, 10, 2023}, 'I', {5, 10, 2023}},
                       {4, "Smith, Roberto", 42597233, {5, 7, 1988}, 'M', {10, 2, 2021}, "ADULTO", {1, 5, 2024}, 'I', {15, 9, 2023}},
                       {15, "Johnson, Tobias", 32597237, {1, 11, 1996}, 'M', {6, 6, 2022}, "ADULTO", {18, 8, 2023}, 'A', {25, 9, 2023}},
                       {13, "Garcia, Samuel", 32597242, {5, 8, 2002}, 'F', {13, 11, 2021}, "ADULTO", {22, 5, 2023}, 'A', {11, 8, 2023}},
                       {16, "Gonzalez, Jorgelina", 42597238, {15, 5, 1997}, 'F', {7, 3, 2020}, "ADULTO", {6, 7, 2023}, 'I', {15, 8, 2023}},
                       {11, "Perez, Johnny", 72597243, {14, 4, 1998}, 'M', {9, 3, 2020}, "ADULTO", {8, 7, 2023}, 'I', {12, 10, 2023}},
                       {19, "Martinez, Julian", 92597236, {20, 3, 2000}, 'M', {9, 8, 2021}, "ADULTO", {8, 4, 2023}, 'I', {12, 10, 2023}},
                       {20, "Perez, Camilo", 82597235, {9, 12, 1992}, 'M', {5, 1, 2022}, "ADULTO", {14, 9, 2023}, 'A', {10, 7, 2023}},
                       {9, "Martinez, Smith", 32597247, {22, 3, 1999}, 'M', {4, 10, 2020}, "ADULTO", {3, 7, 2023}, 'I', {12, 10, 2023}},
                       {17, "Smith, Perez", 72597239, {27, 9, 1993}, 'M', {9, 2, 2022}, "ADULTO", {2, 11, 2023}, 'I', {7, 10, 2023}},
                       {12, "Garcia, Pablo", 72597234, {17, 8, 1999}, 'M', {14, 6, 2020}, "ADULTO", {2, 3, 2023}, 'I', {21, 8, 2023}},
                       {14, "Lopez, Martinez", 12597241, {8, 6, 1994}, 'M', {17, 4, 2023}, "ADULTO", {4, 9, 2023}, 'I', {13, 10, 2023}},
                       {10, "Hernandez, Gonzalo", 12597244, {3, 10, 2003}, 'M', {15, 6, 2021}, "ADULTO", {9, 9, 2023}, 'A', {10, 9, 2023}},
                       {6, "Gonzalez, Carlos", 12597249, {7, 12, 1987}, 'M', {6, 1, 2021}, "ADULTO", {9, 9, 2023}, 'I', {22, 10, 2023}},
                       {3, "Smith, Lucas", 72597251, {29, 11, 2000}, 'M', {4, 7, 2021}, "ADULTO", {12, 4, 2023}, 'I', {15, 10, 2023}},
                       {5, "Diaz, Leonardo", 42597245, {18, 1, 1990}, 'M', {11, 8, 2022}, "ADULTO", {21, 5, 2023}, 'I', {15, 10, 2023}},
                       {8, "Rodriguez, Rigoberta", 82597246, {27, 5, 1995}, 'F', {6, 1, 2021}, "ADULTO", {12, 9, 2023}, 'A', {5, 8, 2023}},
                       {18, "Johnson, Gabriela", 92597240, {13, 2, 1991}, 'F', {1, 10, 2022}, "ADULTO", {15, 3, 2024}, 'A', {20, 9, 2023}},
                       {7, "Lopez, Johnson", 72597248, {11, 9, 2001}, 'F', {2, 6, 2022}, "ADULTO", {8, 4, 2023}, 'A', {7, 11, 2023}},
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

  while(abc[(int)op] > 7){

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

  op = abc[(int)op];

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
