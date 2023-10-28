#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TP.h"

int main(){

  int ret;
  char op;

  //crearLoteDePrueba();

  ret = pasarArchTxtABin("socios.txt","socios.data");

  if(ret!=TODO_OK)
    return ret;

  //crearIndice();

  op = menu();

  while(op!='S'){

    switch(op){

        case('A'):{

          break;

        }
        case('M'):{

          break;

        }
        case('B'):{

          break;

        }
        case('L'):{

          break;

        }
        case('V'):{

          break;

        }
        case('P'):{

          break;

        }
        case('S'):{

          printf("SALIDA CON EXITO\n");
          break;

        }
      }

      if(op != 'S')
        op = menu();
  }

  return 0;

}
