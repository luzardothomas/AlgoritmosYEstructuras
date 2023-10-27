#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  unsigned dia,
           mes,
           anio;
}tFecha;

typedef struct{
  long int nro;
  char nya[61];
  long int dni;
  tFecha nacimiento;
  char sexo;
  tFecha afiliacion;
  char categoria[11];
  tFecha ultimaPaga;
  char estado;
  tFecha baja;
}tSocio;

int validarLoteDeDatosDelClub(tSocio* socio){

  if(!(socio->nro >= 1 && socio->nro <= 10000000))
    return 0;

  if(!(socio->dni >= 10000 && socio->dni <= 100000000))
    return 0;

  if(!(socio->sexo == 'F' || socio->sexo == 'M' || socio->sexo == 'O'))
    return 0;

  if(!((strcmp(socio->categoria,"MENOR") == 0)     ||
       (strcmp(socio->categoria,"CADETE") == 0)    ||
       (strcmp(socio->categoria,"ADULTO") == 0)    ||
       (strcmp(socio->categoria,"VITALICIO") == 0) ||
       (strcmp(socio->categoria,"HONORARIO") == 0) ||
       (strcmp(socio->categoria,"JUBILADO") == 0)))
    return 0;

  if(!(socio->estado == 'A' || socio->estado == 'I'))
    return 0;

  if(socio->estado == 'A'){
    socio->baja.dia = 0;
    socio->baja.mes = 0;
    socio->baja.anio = 0;
  }

  return 1;
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

  if(pf == NULL)
    return 0;
  
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
  
  return 1;
}

int abrirArchivo(FILE** pf, const char* ruta, const char* modo){
  
  *pf = fopen(ruta,modo);
  if(*pf == NULL)
    return 0;
  
  return 1;
}

int leerSocios(FILE** pf,tSocio* socios){
  
  return fscanf(*pf,"%ld|%[^|]|%ld|%d/%d/%d|%c|%d/%d/%d|%[^|]|%d/%d/%d|%c|%d/%d/%d\n",&socios->nro,
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

int main(){
  
    FILE *pf;
    FILE *bin;
    tSocio socios;

    ///crearLoteDePrueba();

    abrirArchivo(&pf,"/home/thomas/Desktop/AlgoritmosYEstructuras/TP/socios.txt","rb");
    abrirArchivo(&bin,"socios.data","wb");

    while(leerSocios(&pf,&socios) > 0){
      mostrarSocios(&socios,stdout);
      grabarSocios(&bin,&socios);
    }

    fclose(pf);
    fclose(bin);

    return 0;
}
