#include "TP.h"
#include <string.h>
#include <time.h>
#ifdef _WIN32
  #include<windows.h>
#endif
///Funciones Utilitarias
void limpiarBuffer(){
  int c;
  /// Descarta el carácter actual y continúa leyendo hasta encontrar '\n' o EOF.
  while ((c = getchar()) != '\n' && c != EOF);
}
void limpiarPantalla(){
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}
int miStrcmpi(const char * cad1, const char * cad2){
  while(*cad1 && *cad2 && A_MAYUS(*cad1) == A_MAYUS(*cad2)){
    cad1++;
    cad2++;
  }
  return *cad1-*cad2;
}
int contarNodos(tNodo* nodo){
  int cont = 0;

  while(nodo){
    cont++;
    nodo = nodo->sig;
  }

  return cont;
}
///Funciones de Archivos
int crearLoteDePrueba(){

  tSocio socios[]  = {
                       {1, "Iacobaccio, Agustina",44263896, {16, 1, 2003}, 'F', {2, 3, 2022}, "ADULTO", {9, 9, 2023}, 'A', {5, 11, 2023}},
                       {2, "Luzardo, Gaston Thomas", 42597231, {27, 1, 2001}, 'M', {1, 1, 2023}, "ADULTO", {5, 10, 2023}, 'I', {5, 10, 2023}},
                       {4, "Smith, Roberto", 42597233, {5, 7, 1988}, 'M', {10, 2, 2021}, "ADULTO", {1, 5, 2024}, 'I', {15, 9, 2023}},
                       {15, "Johnson, Tobias", 32597237, {1, 11, 1996}, 'M', {6, 6, 2022}, "ADULTO", {18, 8, 2023}, 'A', {25, 9, 2023}},
                       {13, "Garcia, Samuel", 32597242, {5, 8, 2002}, 'M', {13, 11, 2021}, "ADULTO", {22, 5, 2023}, 'A', {11, 8, 2023}},
                       {16, "Gonzalez, Jorge Oscar", 42597238, {15, 5, 1997}, 'M', {7, 3, 2020}, "ADULTO", {6, 7, 2023}, 'I', {15, 8, 2023}},
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
                       {8, "Rodriguez, Alberto", 82597246, {27, 5, 1995}, 'M', {6, 1, 2021}, "ADULTO", {12, 9, 2023}, 'A', {5, 8, 2023}},
                       {18, "Johnson, Christopher", 92597240, {13, 2, 1991}, 'M', {1, 10, 2022}, "ADULTO", {15, 3, 2024}, 'A', {20, 9, 2023}},
                       {7, "Lopez, Johnson", 72597248, {11, 9, 2001}, 'M', {2, 6, 2022}, "ADULTO", {8, 4, 2023}, 'A', {7, 11, 2023}},
                       {21, "Bopez, Johnson", 72597249, {11, 9, 2001}, 'M', {2, 6, 2022}, "ADULTO", {8, 4, 2023}, 'A', {7, 11, 2023}},
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
int abrirArchivo(FILE** pf, const char* ruta, const char* modo){

  *pf = fopen(ruta,modo);

  if(*pf == NULL)
    return ERROR_ARCH;

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

  while(leerSocios(&socios,&pf) > 0){

    mostrarSocios(&socios,stdout);
    grabarSocios(&bin,&socios);

  }

  fclose(pf);
  fclose(bin);

  return TODO_OK;
}
///Funciones de Fecha
int esBisiesto(unsigned anio){
  return ((anio % 4 == 0 && anio % 100 != 0) || anio % 400 == 0);
}
int validarFecha(tFecha fecha){
  int dias[] = {31,28,31,30,31,30,31,31,30,31,30,31};

  if(!(fecha.mes >= 1 && fecha.mes <= 12))
    return ERROR_REGIS;

  esBisiesto(fecha.anio) ? dias[1]++ : 0;

  if(!(fecha.dia >= 1 && fecha.dia <= dias[fecha.mes-1]))
    return ERROR_REGIS;

  return TODO_OK;
}
///Funciones de Menu
int menu(){
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

  ///S = 0

  ///A = 1
  ///B = 2
  ///L = 3
  ///M = 4
  ///P = 5
  ///V = 6

  do{

    mostrarMenu();

    op = completarMenu();

    if(ES_LETRA(op)){
      op = A_MAYUS(op);
      op -= 65;
    }
    else{
      printf("OPCION NO VALIDA\n\n");
      op = 3;
    }
  }
  while(abc[(int)op] > 7);

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
char completarMenu(){
  char op;
  scanf("%c",&op);
  limpiarBuffer();
  return op;
}
///Funciones de Socios
tSocio completarDatos(){
  tSocio socio;

  #define LLENAR_DATOS
  #ifdef LLENAR_DATOS

  strcpy(socio.nya,"Mercury, Freddie \0");
  socio.dni = 18951723;
  socio.nacimiento.dia = 1;
  socio.nacimiento.mes = 1;
  socio.nacimiento.anio = 2001;
  socio.sexo = 'M';
  socio.afiliacion.dia = 22;
  socio.afiliacion.mes = 1;
  socio.afiliacion.anio = 2023;
  strcpy(socio.categoria,"Adulto");
  socio.ultimaPaga.dia = 28;
  socio.ultimaPaga.mes = 11;
  socio.ultimaPaga.anio = 2023;
  socio.estado = 'A';
  return socio;

  #endif // LLENAR_DATOS

  printf("Numero de socio: ");
  scanf("%ld",&socio.nro);

  limpiarBuffer();

  printf("Apellido,nombre completo: ");
  scanf("%60[^\n]",socio.nya);

  printf("Dni: ");
  scanf("%ld",&socio.dni);

  printf("Fecha de nacimiento (dd/mm/aaaa): ");
  scanf("%d/%d/%d",&socio.nacimiento.dia,
                   &socio.nacimiento.mes,
                   &socio.nacimiento.anio);

  limpiarBuffer();

  printf("Sexo ('M' (Masculino)/'F' (Femenino) /'O' (Otro planeta como Namekusei)): ");
  scanf("%c",&socio.sexo);

  printf("Fecha de afiliacion (dd/mm/aaaa): ");
  scanf("%d/%d/%d",&socio.afiliacion.dia,
                   &socio.afiliacion.mes,
                   &socio.afiliacion.anio);

  limpiarBuffer();

  printf("Categoria ('MENOR'/'CADETE'/'ADULTO'/'VITALICIO'/'HONORARIO'/'JUBILADO'):");
  scanf("%10[^\n]",socio.categoria);

  printf("Fecha de ultima cuota pagada (dd/mm/aaaa): ");
  scanf("%d/%d/%d",&socio.ultimaPaga.dia,
                   &socio.ultimaPaga.mes,
                   &socio.ultimaPaga.anio);

  limpiarBuffer();

  printf("Estado ('A' (Activo)/'I' (Inactivo)):");
  scanf("%c",&socio.estado);

  if(A_MAYUS(socio.estado) == 'I'){
    printf("Fecha de baja (dd/mm/aaaa): ");
    scanf("%d/%d/%d",&socio.baja.dia,
                     &socio.baja.mes,
                     &socio.baja.anio);
  }
  return socio;
}
int validarLoteDeDatosDelClub(tSocio* socio){

  if(!(socio->nro >= 1 && socio->nro <= 10000000))
    return ERROR_REGIS;

  if(!(socio->dni >= 10000 && socio->dni <= 100000000))
    return ERROR_REGIS;

  if(!(A_MAYUS(socio->sexo) == 'F' || A_MAYUS(socio->sexo) == 'M' || A_MAYUS(socio->sexo) == 'O'))
    return ERROR_REGIS;

  if(!((miStrcmpi(socio->categoria,"MENOR") == 0)     ||
       (miStrcmpi(socio->categoria,"CADETE") == 0)    ||
       (miStrcmpi(socio->categoria,"ADULTO") == 0)    ||
       (miStrcmpi(socio->categoria,"VITALICIO") == 0) ||
       (miStrcmpi(socio->categoria,"HONORARIO") == 0) ||
       (miStrcmpi(socio->categoria,"JUBILADO") == 0)))
    return ERROR_REGIS;

  if(!(A_MAYUS(socio->estado) == 'A' || A_MAYUS(socio->estado) == 'I'))
    return ERROR_REGIS;

  if(A_MAYUS(socio->estado) == 'A'){
    socio->baja.dia = 0;
    socio->baja.mes = 0;
    socio->baja.anio = 0;
  }
  else
    if(!validarFecha(socio->baja))
      return ERROR_REGIS;

  if(!validarFecha(socio->nacimiento))
    return ERROR_REGIS;

  if(!validarFecha(socio->ultimaPaga))
    return ERROR_REGIS;

  if(!validarFecha(socio->afiliacion))
    return ERROR_REGIS;

  return TODO_OK;
}
int leerSocios(void* a,FILE** pf){
  tSocio* socios = (tSocio*)a;
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
void grabarSocios(FILE** pf, tSocio* socios){

  fwrite(socios,sizeof(tSocio),1,*pf);

}
void mostrarSocios(const void*a, FILE* pf){
  tSocio* socios = (tSocio*)a;
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
int compararDiasDeAtraso(const void* fecha1, const void* fecha2){

  int dato1 = (((tSocio*)(fecha1))->ultimaPaga.dia - ((tSocio*)(fecha1))->afiliacion.dia);
  int dato2 = (((tSocio*)(fecha2))->ultimaPaga.dia - ((tSocio*)(fecha2))->afiliacion.dia);

  return dato1-dato2;
}
int insertarSocioAtrasado(tLista* pl,const void* dato, size_t tam, cmp comp){
  tNodo* nue;

  while(*pl && comp((*pl)->dato,dato) <= 0)
    pl = &(*pl)->sig;

  nue = (tNodo*)malloc(sizeof(tNodo));

  if(nue == NULL)
    return 0;

  nue->dato = malloc(tam);

  if(nue->dato == NULL){
    free(nue);
    return 0;
  }
  memcpy(nue->dato,dato,tam);
  nue->tam = tam;
  nue->sig = *pl;
  *pl = nue;
  return 1;
}
///Funciones de Accion
int darDeAlta(tIndice* pin,unsigned* nroReg,FILE* pf){
  tSocio socio;
  tSocio teclado;

  do{
      teclado = completarDatos();
      printf("\nIngrese el numero de socio:");
      scanf("%ld",&teclado.nro);
    }while(validarLoteDeDatosDelClub(&teclado) != 1);

  rewind(pf);

  fread(&socio,sizeof(tSocio),1,pf);

  while(!feof(pf)){
    if(teclado.nro == socio.nro){
      if(A_MAYUS(socio.estado) == 'A')
      printf("\nEl numero de socio %ld Numero de Registro %d solicitado se encuentra en estado activo\n",socio.nro,*nroReg);
      else{
        socio.estado = 'A';
        socio.baja.dia = 0;
        socio.baja.mes = 0;
        socio.baja.anio = 0;
        fflush(pf);
        fseek(pf,sizeof(tSocio)*(*nroReg),SEEK_SET);
        fwrite(&socio,sizeof(tSocio),1,pf);
      }
      return ENCONTRADO;
    }
    fflush(pf);
    fread(&socio,sizeof(tSocio),1,pf);
  }

  fflush(pf);
  fwrite(&teclado,sizeof(tSocio),1,pf);

  if(A_MAYUS(teclado.estado) == 'I')
    return INACTIVO;

  memcpy(pin->regInd,&teclado.nro,pin->tamClave);
  memcpy((char*)pin->regInd + pin->tamClave,nroReg,sizeof(unsigned));

  if(!ponerAlFinal(&pin->lista,pin->regInd,pin->tamClave + sizeof(unsigned)))
    return SIN_MEM;

  (*nroReg)++;

  return NO_ENCONTRADO;
}
int darDeBaja(tIndice* pin,unsigned* nroReg,FILE* pf){
  tSocio socio;
  tSocio teclado;

  long int diferencia;

  time_t tiempo1;
  time_t tiempo2;

  struct tm tmFecha1 = {0};
  struct tm tmFecha2 = {0};


  do{
      printf("Escriba el Nro de Socio:");
      scanf("%ld",&teclado.nro);
    }while(!(teclado.nro >= 1 && teclado.nro <= 10000000));

  rewind(pf);

  if(buscarIndice(pin,&teclado.nro,nroReg)){

    fflush(pf);

    fread(&socio,sizeof(tSocio),1,pf);
    while(socio.nro != teclado.nro)
      fread(&socio,sizeof(tSocio),1,pf);

    printf("La fecha de afilicacion es: %02d/%02d/%04d",socio.afiliacion.dia,
                                                        socio.afiliacion.mes,
                                                        socio.afiliacion.anio);

    tmFecha1.tm_year = socio.afiliacion.anio - 1900;
    tmFecha1.tm_mon = socio.afiliacion.mes - 1;
    tmFecha1.tm_mday = socio.afiliacion.dia;

    tiempo1 = mktime(&tmFecha1);

    do{
      limpiarPantalla();
      printf("La fecha de afilicacion es: %02d/%02d/%04d",socio.afiliacion.dia,
                                                          socio.afiliacion.mes,
                                                          socio.afiliacion.anio);
      printf("\nEscriba la fecha de baja (dd/mm/aaaa):");
      scanf("%d/%d/%d",&teclado.baja.dia,
                       &teclado.baja.mes,
                       &teclado.baja.anio);



      tmFecha2.tm_year = teclado.baja.anio - 1900;
      tmFecha2.tm_mon = teclado.baja.mes - 1;
      tmFecha2.tm_mday = teclado.baja.dia;

      tiempo2 = mktime(&tmFecha2);

      diferencia = difftime(tiempo2,tiempo1);


    }while(!(validarFecha(teclado.baja) && diferencia >= 0));


    eliminarIndice(pin,pin->regInd,nroReg);

    fflush(pf);

    socio.estado = 'I';
    socio.baja = teclado.baja;

    fseek(pf,-1*sizeof(tSocio),SEEK_CUR);
    fwrite(&socio,sizeof(tSocio),1,pf);

    printf("\nLa operacion fue exitosa\n");

    return ENCONTRADO;
  }

  fread(&socio,sizeof(tSocio),1,pf);

  while(!feof(pf)){

    if(teclado.nro == socio.nro){
      printf("\nEl socio %ld ya estaba dado de baja\n",socio.nro);
      return INACTIVO;
    }

    fread(&socio,sizeof(tSocio),1,pf);
  }

  printf("\nEl Socio %ld nunca existio\n",teclado.nro);

  return NO_EXISTE;
}
///Teniendo en cuenta los Inactivos
int modificarAyN(tIndice* pin,unsigned* nroReg,FILE* pf){
  tSocio socio;
  tSocio teclado;

  do{
      printf("Escriba el Nro de Socio:");
      scanf("%ld",&teclado.nro);
    }while(!(teclado.nro >= 1 && teclado.nro <= 10000000));

  rewind(pf);

  fread(&socio,sizeof(tSocio),1,pf);

  while(!feof(pf)){
    if(teclado.nro == socio.nro){

      printf("Escriba el apellido y nombre:");
      limpiarBuffer();
      scanf("%60[^\n]",socio.nya);

      fseek(pf,-sizeof(tSocio),SEEK_CUR);
      fflush(pf);
      fwrite(&socio,sizeof(tSocio),1,pf);

      printf("\nLa modificacion del apellido y nombre fue exitosa\n");

      return ENCONTRADO;
    }

    fflush(pf);
    fread(&socio,sizeof(tSocio),1,pf);

  }

  printf("\nNo se pudo encontrar el socio solicitado\n");

  return NO_ENCONTRADO;
}
/** Misma función de arriba sin tener en cuenta los Inactivos
int modificarAyN(tIndice* pin,unsigned* nroReg,FILE* pf){
  tSocio socio;
  tNodo* buscar = NULL;

  do{
      //printf("Escriba el Nro de Socio:");
      //scanf("%ld",&socio.nro);
      socio.nro = 14;
    }while(!(socio.nro >= 1 && socio.nro <= 10000000));

  rewind(pf);

  if((buscar = buscarOcurrencia(&pin->lista,&socio.nro,pin->comp))){
    //printf("Escriba el apellido y nombre:");
    //limpiarBuffer();
    //scanf("%60[^\n]",copia);
    memcpy(nroReg,(char*)buscar->dato + pin->tamClave,sizeof(unsigned));
    fseek(pf,sizeof(tSocio)*(*nroReg),SEEK_SET);
    fread(&socio,sizeof(tSocio),1,pf);
    strcpy(socio.nya,"Ritchie, Lionel");
    mostrarSocios(&socio,stdout);
    fflush(pf);
    fseek(pf,sizeof(tSocio)*(*nroReg),SEEK_SET);
    fwrite(&socio,sizeof(tSocio),1,pf);
    return ENCONTRADO;
  }
  return NO_ENCONTRADO;
}
*/
int listarSociosDeBaja(tIndice* pin,unsigned* nroReg,FILE* pf){
  tSocio socio;

  rewind(pf);

  printf("\n============================ SOCIOS DADOS DE BAJA ============================\n");

  fread(&socio,sizeof(tSocio),1,pf);
  while(!feof(pf)){

    mostrarSocios(&socio,stdout);
    fread(&socio,sizeof(tSocio),1,pf);

  }

  return TODO_OK;
}
int verSociosActivos(tIndice* pin,unsigned* nroReg,FILE* pf){
  tLista* lista = (tLista*)&pin->lista;
  tSocio socio;

  if(!*lista)
    return INDICE_VACIO;

  rewind(pf);

  printf("\n============================ SOCIOS ACTIVOS ============================\n");

  while(*lista){

    memcpy(nroReg,(char*)(*lista)->dato + pin->tamClave,sizeof(unsigned));

    fseek(pf,sizeof(tSocio)*(*nroReg),SEEK_SET);
    fread(&socio,sizeof(tSocio),1,pf);

    mostrarSocios(&socio,stdout);

    lista = &(*lista)->sig;
  }

  return TODO_OK;
}
int verMayoresDeudores(tIndice* pin,unsigned* nroReg,FILE* pf){
  tLista lista = NULL;
  tSocio socio;
  unsigned iteraciones = 10;

  if(!pin->lista)
    return INDICE_VACIO;

  rewind(pf);
  fflush(pf);

  fread(&socio,sizeof(tSocio),1,pf);

  while(!feof(pf)){

    if((socio.ultimaPaga.dia - socio.afiliacion.dia) > 0 && socio.estado == 'A')
      if(!insertarSocioAtrasado(&lista,&socio,sizeof(tSocio),compararDiasDeAtraso))
        return SIN_MEM;

    fread(&socio,sizeof(tSocio),1,pf);
  }

  if(contarNodos(lista) < 10){
    vaciarLista(&lista);
    return POCOS_SOCIOS;
  }

  printf("\n============================ TOP 10 SOCIOS MOROSOS ============================\n");

  ///Muestra solo los diez primeros

  while(iteraciones--){
    mostrarSocios(lista->dato,stdout);
    lista = lista->sig;
  }

  vaciarLista(&lista);

  return TODO_OK;
}
