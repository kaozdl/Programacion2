/* 4580203 - 4660754 */

#include <assert.h>
#include <stdlib.h>
#include "../include/utils.h"
#include "../include/texto.h"
#include "../include/info.h"
#include "../include/lista.h"
#include "../include/binario.h"
#include "../include/conjunto.h"
#include "../include/cola_de_prioridad.h"


struct nodo {
    prio_t prioridad;
    lista elementos;
};

struct rep_cola_prioridad{
    nodo *datos;
    bool *esta_prioridad;
    nat tope;
    nat capacidad;
};




cola_de_prioridad crear_cp(nat tamanio){
    assert (tamanio > 0);
    cola_de_prioridad cp = new rep_cola_prioridad;
    cp->datos = new nodo[tamanio+1];
    cp->esta_prioridad = new bool[tamanio+1];
    cp->tope = 0;
    cp->capacidad = tamanio;
    for (nat K = 0; K <= tamanio+1; K++) {
        cp->esta_prioridad[K]= false;
    }
    return cp;
}
void filtrado_ascendente(cola_de_prioridad &c, int pos, const nat p){
 if (pos>1 && c->datos[pos/2].prioridad>p){
    nodo cambio = c->datos[pos];
    c->datos[pos]=c->datos[pos/2];
    c->datos[pos/2]=cambio;
    filtrado_ascendente(c,pos/2,p);
  }
}

void insertar_en_cp(const info_t i, prio_t p, cola_de_prioridad &c){
  if (hay_prioridad(p,c)){
    nat pos=1;
    while(pos <= c->tope && c->datos[pos].prioridad != p)
      pos++;
    localizador loc = final_lista(c->datos[pos].elementos);
    insertar_despues(i,loc,c->datos[pos].elementos);
  }
  else{
    c->tope++;
    c->datos[c->tope].elementos = crear_lista();
    c->datos[c->tope].prioridad = p;
    localizador loc = NULL;
    insertar_despues(copiar_info(i),loc,c->datos[c->tope].elementos);
    nat pos = c->tope;
    filtrado_ascendente(c,pos,p);
    c->esta_prioridad[p] = true;
  }
 }


void filtrado_descendente(cola_de_prioridad &c , nat pos){
  while ((2*pos <= c->tope && c->datos[2*pos].prioridad < c->datos[pos].prioridad) || (2*pos+1 <= c->tope && c->datos[2*pos+1].prioridad < c->datos[pos].prioridad)){
    if (2*pos+1<=c->tope && c->datos[2*pos].prioridad>c->datos[2*pos+1].prioridad ){
      nodo cambio = c->datos[pos];
      c->datos[pos]=c->datos[2*pos+1];
      c->datos[2*pos+1]=cambio;
      pos=2*pos+1;
    }
    else{
      nodo cambio = c->datos[pos];
      c->datos[pos]=c->datos[2*pos];
      c->datos[2*pos]=cambio;
      pos=2*pos;
    }
  }
 }

void eliminar_prioritario(cola_de_prioridad &c){
  if (!es_vacia_cp(c)){
    lista l = c->datos[1].elementos;
    localizador loc = inicio_lista(l);
    remover_de_lista(loc,l);
    if (es_vacia_lista(l)){
      c->esta_prioridad[c->datos[1].prioridad] = false;
      liberar_lista(l);
      c->datos[1]=c->datos[c->tope];
      c->tope--;
      nat pos = 1;
      filtrado_descendente(c,pos);
    }
  }
}

void liberar_cp(cola_de_prioridad &c) {
  delete [] c->datos;
  delete c;
 }

bool es_vacia_cp(const cola_de_prioridad c){
  return c->tope == 0;
 }

bool es_llena_cp(const cola_de_prioridad c){
 return c->tope == c->capacidad;
 }

bool hay_prioridad(const prio_t p, const cola_de_prioridad c){
  return c->esta_prioridad[p];
 }

lista lista_en_cp(const prio_t p, const cola_de_prioridad c){
  lista l = crear_lista();
  if (!c->esta_prioridad[p]){
    return l;
  }
  else{
    nat cont =1;
    while(c->datos[cont].prioridad!=p)
      cont++;
    return c->datos[cont].elementos;
  }
 }

info_t prioritario(const cola_de_prioridad c){
  return info_lista(inicio_lista(c->datos[1].elementos),c->datos[1].elementos);
}

prio_t valor_prioritario(const cola_de_prioridad c){
  return c->datos[1].prioridad;
}
