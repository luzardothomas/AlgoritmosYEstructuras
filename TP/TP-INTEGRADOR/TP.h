#ifndef TP_H_INCLUDED
#define TP_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista/lista.h"
#include "indice/indice.h"
#define TODO_OK 1
#define ERROR_ARCH 0
#define ERROR_REGIS 0
#define VALOR_ABSOLUTO(x) (((x) < 0) ? (-x) : (x))
#define ES_LETRA(x) (((x) >= 'a' && (x) <= 'z') || ((x) >= 'A' && (x) <= 'Z'))
#define A_MAYUS(x)    (((x) >= 'a' && (x) <= 'z') ? ((x)-(' ')) : (x))
#define menor(a,b)      ((a)<(b) ? (a):(b))
#define mayor(a,b)      ((a)>(b) ? (a):(b))
typedef struct{

  unsigned dia,
           mes,
           anio;

}
tFecha;
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

}
tSocio;
typedef int (*fOpcion)(tIndice*,unsigned*,FILE*);

///Funciones Utilitarias

void limpiarPantalla();
void limpiarBuffer();
int miStrcmpi(const char * cad1, const char * cad2);
int contarNodos(tNodo* nodo);

///Funciones de Archivos

int crearLoteDePrueba();
int abrirArchivo(FILE** pf, const char* ruta, const char* modo);
int pasarArchTxtABin(const char* rutaTxt,const char* rutaBin);

///Funciones de Fechas

int esBisiesto(unsigned anio);
int validarFecha(tFecha fecha);

///Funciones de Menu

char completarMenu();
int menu();
void mostrarMenu();

///Funciones de Socios

tSocio completarDatos();
int validarLoteDeDatosDelClub(tSocio* socio);
int leerSocios(void* a,FILE** pf);
void grabarSocios(FILE** pf, tSocio* socios);
void mostrarSocios(const void* a, FILE* pf);
int compararAtrasoDeSocios(const void* socio1, const void* socio2);
int insertarSocioAtrasado(tLista* pl,const void* dato, size_t tam, cmp comp);

///Gestión de Socios

int darDeAlta(tIndice* pin,unsigned* nroReg,FILE* pf);
int darDeBaja(tIndice* pin,unsigned* nroReg,FILE* pf);
int modificarAyN(tIndice* pin,unsigned* nroReg,FILE* pf);
int listarSociosDeBaja(tIndice* pin,unsigned* nroReg,FILE* pf);
int verSociosActivos(tIndice* pin,unsigned* nroReg,FILE* pf);
int verMayoresDeudores(tIndice* pin,unsigned* nroReg,FILE* pf);

#endif // TP_H_INCLUDED
