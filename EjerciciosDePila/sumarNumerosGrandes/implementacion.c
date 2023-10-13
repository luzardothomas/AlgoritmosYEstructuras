#include "implementacion.h"
#include <stdio.h>
#define PROCESO_DETALLADO
int sumarNumerosGrandes(tPila* pila1,tPila* pila2,tPila* pila3,int iterador,char* cad1,char* cad2){
  int retorno1,retorno2,retorno3,carry,n1,n2;
  char p;
  while(iterador-- > 0){

    retorno1 = desapilar(pila1,&p,sizeof(char));
    if(retorno1){
      n1 = p - 48;
      #ifdef PROCESO_DETALLADO
      printf("n1 %d\n",n1);
      #endif
    }
    else
      n1 = 0;
    retorno2 = desapilar(pila2,&p,sizeof(char));
    if(retorno2){
      n2 = p - 48;
      #ifdef PROCESO_DETALLADO
      printf("n2 %d\n----------------\n",n2);
      #endif
    }
    else
      n2 = 0;
    if(carry && retorno3){
      retorno3 = desapilar(pila3,&p,sizeof(char));
      #ifdef PROCESO_DETALLADO
      printf("Desapile el carry de la pila 3 este dato: %c\n**************************\n",p);
      #endif
      carry = p - 48;
    }
    else
      carry = 0;
    n1 += n2;
    #ifdef PROCESO_DETALLADO
    printf("n1+n2 %d\n-----------------\n",n1);
    #endif
    n1 += carry;
    #ifdef PROCESO_DETALLADO
    printf("n1+carry %d\n",n1);
    #endif
    carry = n1 / 10;
    #ifdef PROCESO_DETALLADO
    printf("carry %d\n",carry);
    #endif
    n1 %= 10;
    p = n1 + 48;

    if(n1 >= 0){
      #ifdef PROCESO_DETALLADO
      printf("Cargue a la pila 3 este dato: %c\n**************************\n",p);
      #endif
      retorno3 = apilar(pila3,&p,sizeof(char));
    }

    p = carry + 48;

    if(carry){
      #ifdef PROCESO_DETALLADO
      printf("Cargue el carry a la pila 3 este dato: %c\n**************************\n",p);
      #endif
      retorno3 = apilar(pila3,&p,sizeof(char));
    }
  }
  return carry;
}
