#ifndef TP_H_INCLUDED
#define TP_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "indice/indice.h"
#include "lista/lista.h"

#define TODO_OK 1
#define ERROR_ARCH 0
#define ERROR_REGIS 0

#define miToupper(c)    (c)>=('a') && (c)<=('z') ? (c)- (' ') : (c)
#define menor(a,b)      (a)<(b)? (a):(b)
#define mayor(a,b)      (a)>(b)? (a):(b)

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

//typedef (*fOpcion)(tSocio*,FILE*);

int crearLoteDePrueba();
int pasarArchTxtABin(const char* rutaTxt,const char* rutaBin);
int validarLoteDeDatosDelClub(tSocio* socio);
int abrirArchivo(FILE** pf, const char* ruta, const char* modo);
int leerSocios(FILE** pf,tSocio* socios);
void mostrarSocios(const tSocio* socios, FILE* pf);
void grabarSocios(FILE** pf, tSocio* socios);
char menu();
void mostrarMenu();

#endif // TP_H_INCLUDED
