#include "colaEst.h"
void crear_cola(t_cola *pc){
  pc->fin = 0;
  pc->ini = 0;
  pc->tamDisp = TAM_COLA;
}

/// ========================================== ESTÁNDAR ==========================================

int a_colar(t_cola* pc, const void* dato, size_t tam){
  size_t ini, fin;

  if (pc->tamDisp < sizeof(size_t) + tam)
      return 0;

  if ((ini = minimo(sizeof(tam), TAM_COLA - pc->fin)) != 0)
    memcpy(pc->cola + pc->fin, &tam, ini);

  if ((fin = sizeof(tam) - ini) != 0)
    memcpy(pc->cola, ((char*)&tam) + ini, fin);

  pc->fin = fin ? fin : pc->fin + ini;

  if ((ini = minimo(tam, TAM_COLA - pc->fin)) != 0)
    memcpy(pc->cola + pc->fin, dato, ini);

  if ((fin = tam - ini) != 0)
    memcpy(pc->cola, ((char *)dato) + ini, fin);

  pc->fin = fin ? fin : pc->fin + ini;

  pc->tamDisp -= sizeof(size_t) + tam;

  return 1;
}

int des_acolar(t_cola* pc, void* dato, size_t tam){
  size_t ini,fin,tamDato;

  if(pc->tamDisp == TAM_COLA)
    return 0;

  if ((ini = minimo(sizeof(tam), TAM_COLA - pc->ini)) != 0)
    memcpy(&tamDato,pc->cola + pc->ini,ini);

  if ((fin = sizeof(tam) - ini) != 0)
    memcpy(((char*)&tamDato) + ini, pc->cola , fin);

  pc->ini = fin ? fin : pc->ini + ini;
  tamDato = minimo(tamDato,tam);

  if ((ini = minimo(tamDato, TAM_COLA - pc->ini)) != 0)
    memcpy(dato,pc->cola + pc->ini,ini);

  if ((fin = tamDato - ini) != 0)
    memcpy((char*)dato + ini, pc->cola , fin);

  pc->ini = fin ? fin : pc->ini + ini;
  pc->tamDisp += sizeof(size_t) + tamDato;

  return 1;
}


/// ========================================== PRIMITIVAS ===========================================

int cola_vacia(const t_cola* pc){
  return pc->tamDisp == TAM_COLA;
}

int cola_llena(const t_cola *pc, size_t tam){
  return pc->tamDisp == 0;
}

int ver_primero_cola(const t_cola *pc, void *dato, size_t tam){
  size_t ini,fin,tamDato,pos = pc->ini;

  if(pc->tamDisp == TAM_COLA)
    return 0;

  if ((ini = minimo(sizeof(tam), TAM_COLA - pc->ini)) != 0)
    memcpy(&tamDato,pc->cola + pos,ini);

  if ((fin = sizeof(tam) - ini) != 0)
    memcpy(((char*)&tamDato) + ini, pc->cola,fin);

  pos = fin ? fin : pc->ini + fin;
  tamDato = minimo(tamDato,tam);

  if ((ini = minimo(tamDato,TAM_COLA - pos)) != 0)
    memcpy(dato,pc->cola + pos,ini);

  if ((fin = tamDato - ini) != 0)
    memcpy(((char*)dato) + ini, pc->cola,fin);

  return 1;
}

void vaciar_cola(t_cola* pc){
  pc->fin = pc->ini;
  pc->tamDisp = TAM_COLA;
}


/// *************************************************************************************************
/// *************************************************************************************************
/// *************************************************************************************************
/// *************************************************************************************************
/// *************************************************************************************************

/// ========================================== ESTÁNDAR V2 ==========================================

int acolar_(t_cola* pc, const void* dato, size_t tam){
  size_t ini, fin;

  if(pc->tamDisp < sizeof(tam) + tam)
    return 0;

  pc->tamDisp -= sizeof(tam) + tam;

  if((ini = minimo(sizeof(tam),TAM_COLA - pc->fin)) != 0)
    memcpy(pc->cola + pc->fin , &tam , ini);

  ///Si el size_t vino cortado el dato viene entero, no hace falta preguntarlo

  if((fin = sizeof(tam) - ini) != 0){
    memcpy(pc->cola , ((char*)&tam) + ini , fin);
    pc->fin = fin;
    memcpy(pc->cola + pc->fin , dato , tam);
    pc->fin = pc->fin + tam;
    return 1;
  }

  pc->fin = pc->fin + ini;

  if((ini = minimo(tam,TAM_COLA - pc->fin)) != 0)
    memcpy(pc->cola + pc->fin , dato , ini);


  if((fin = tam - ini) != 0)
    memcpy(pc->cola , ((char*)dato) + ini , fin);

  pc->fin = fin ? fin : pc->fin + ini;

  return 1;
}

int desacolar_(t_cola* pc, void* dato, size_t tam){
  size_t ini,fin,tamDato;

  if(pc->tamDisp == TAM_COLA)
    return 0;

  if((ini = minimo(sizeof(tam),TAM_COLA - pc->ini)) != 0)
    memcpy(&tamDato , pc->cola + pc->ini , ini);

  ///Si el size_t vino cortado el dato viene entero, no hace falta preguntarlo

  if((fin = sizeof(tam) - ini) != 0){
    memcpy(((char*)&tamDato) + ini , pc->cola , fin);
    pc->ini = fin;
    tamDato = minimo(tam,tamDato);
    pc->tamDisp += sizeof(tam) + tamDato;
    memcpy(dato, pc->cola + pc->ini,tamDato);
    pc->ini = pc->ini + tamDato;
    return 1;
  }

  pc->ini =  pc->ini + ini;
  tamDato = minimo(tam,tamDato);
  pc->tamDisp += sizeof(tam) + tamDato;

  if((ini = minimo(tamDato,TAM_COLA - pc->ini)) != 0)
    memcpy(dato, pc->cola + pc->ini  , ini);

  if((fin = tamDato - ini) != 0)
    memcpy(((char*)dato) + ini , pc->cola , fin);

  pc->ini = fin ? fin : pc->ini + ini;

  return 1;
}

/// ========================================== MI VERSIÓN ==========================================

int acolar__(t_cola *pc, const void *dato, size_t tam){
  size_t* tamDato = &tam;

  if(pc->tamDisp < sizeof(size_t) + tam)
    return 0;

  if(pc->fin == TAM_COLA)
    pc->fin = 0;

  if(TAM_COLA - pc->fin < sizeof(size_t)){
    memcpy(pc->cola + pc->fin,tamDato,TAM_COLA - pc->fin);
    memcpy(pc->cola,((char*)tamDato) + (TAM_COLA - pc->fin),sizeof(size_t) - (TAM_COLA - pc->fin));
    pc->fin = sizeof(size_t) - (TAM_COLA - pc->fin);
  }
  else{
    memcpy(pc->cola + pc->fin,&tam,sizeof(size_t));
    pc->fin += sizeof(size_t);
  }

  if(TAM_COLA - pc->fin < tam){
    memcpy(pc->cola + pc->fin,dato,TAM_COLA - pc->fin);
    memcpy(pc->cola,((char*)dato)+(TAM_COLA - pc->fin),tam - (TAM_COLA - pc->fin));
    pc->fin = tam - (TAM_COLA - pc->fin);
  }
  else{
    memcpy(pc->cola + pc->fin,dato,tam);
    pc->fin += tam;
  }

  pc->tamDisp -= sizeof(size_t) + tam;

  return 1;
}

int desacolar__(t_cola *pc, void *dato, size_t tam){
  size_t menor,tD;
  size_t * tamDato = &tD;

  if(pc->tamDisp == TAM_COLA){
    pc->ini = 0;
    pc->fin = 0;
    return 0;
  }

  if(pc->ini == TAM_COLA)
    pc->ini = 0;

  if(TAM_COLA - pc->ini < sizeof(size_t)){
    memcpy(tamDato,pc->cola + pc->ini, TAM_COLA - pc->ini);
    memcpy(((char*)tamDato)+ (TAM_COLA - pc->ini),pc->cola, sizeof(size_t) - (TAM_COLA - pc->ini));
    pc->ini = sizeof(size_t) - (TAM_COLA - pc->ini);
  }
  else{
    memcpy(tamDato,pc->cola + pc->ini,sizeof(size_t));
    pc->ini += sizeof(size_t);
  }

  menor = MENOR(tam,tD);

  if(TAM_COLA - pc->ini < menor){
    memcpy(dato,pc->cola + pc->ini, TAM_COLA - pc->ini);
    memcpy(((char*)dato)+(TAM_COLA - pc->ini),pc->cola, menor - (TAM_COLA - pc->ini));
    pc->ini = menor - (TAM_COLA - pc->ini);
  }
  else{
    memcpy(dato,pc->cola + pc->ini,menor);
    pc->ini += menor;
  }

  pc->tamDisp += sizeof(size_t) + menor;

  return 1;
}
