#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define minimo(x,y) ((x) < (y) ? (x) : (y))

typedef struct{
  int dni;
  char nya[51];
  float promedio;
}tAlumno;

typedef struct sNodo{
  void* dato;
  size_t tam;
  struct sNodo* sig;
}tNodo;

typedef tNodo* tLista;

void crearIndice(tLista* pl){
  *pl = NULL;
}

int insertarIndice(tLista* pl,const void* dato, size_t tam,
                 int (*cmp)(const void*, const void*)){
  tNodo* nue;

  while(*pl && cmp(dato,(*pl)->dato) < 0)
    pl = &(*pl)->sig;

  if(*pl && cmp((*pl)->dato,dato) == 0)
    return 2;

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

int mostrarLista(const tLista* pl, void (*mostrar)(const void*,FILE*),FILE* pf){
  int cant = 0;
  while(*pl){
    mostrar((*pl)->dato,pf);
    pl = &(*pl)->sig;
    cant++;
  }
  return cant;
}

int grabarIndice(FILE** ind,tLista* indice,size_t tam){
  if(*ind == NULL || *indice == NULL)
    return 0;
  while(*indice){
    fwrite((*indice)->dato,minimo((*indice)->tam,tam),1,*ind);
    indice = &(*indice)->sig;
  }

  return 1;
}

void mostrarIndice(const void* a,FILE *pf){
  tAlumno* pa = (tAlumno*)a;
  fprintf(pf,"%d %s %.2f\n",pa->dni,
                        pa->nya,
                        pa->promedio);
}

int compararDNI(const void* a, const void* b){
  tAlumno* pa = (tAlumno*)a;
  tAlumno* pb = (tAlumno*)b;
  return pa->dni-pb->dni;
}

void crearLoteDePrueba(){
  FILE* pf;
  pf = fopen("alumno.bin","wb");
  tAlumno alum[] = {
                     {44,"A I",10},
                     {42,"T L",8.8},
                     {52,"A C",8.8},
                     {58,"A D",8.8},
                     {18,"A E",8.8},
                     {32,"A F",8.8},
                     {22,"A G",8.8},
                     {56,"A H",8.8},
                   };
  fwrite(alum,sizeof(alum),1,pf);
  fclose(pf);
}



int abrirArchivo(FILE** pf,const char* nombre, const char* modo){
  *pf = fopen(nombre,modo);
  if(pf == NULL)
    return 0;
  return 1;
}

int main(){
  tLista indice;
  FILE *pf;
  FILE *ind;
  tAlumno alu;
  crearLoteDePrueba();
  abrirArchivo(&pf,"alumno.bin","rb");

  crearIndice(&indice);
  ind = fopen("indice.bin","wb");
  fread(&alu,sizeof(alu),1,pf);
  insertarIndice(&indice,&alu,sizeof(alu),compararDNI);
  while(!feof(pf)){
    fread(&alu,sizeof(alu),1,pf);
    insertarIndice(&indice,&alu,sizeof(alu),compararDNI);
  }
  grabarIndice(&ind,&indice,sizeof(alu));
  mostrarLista(&indice,mostrarIndice,stdout);
  fclose(ind);
  return 0;
}
