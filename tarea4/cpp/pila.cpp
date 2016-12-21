/* 4580203 - 4660754 */

#include <stdio.h>
#include <stdlib.h>

#include "../include/texto.h"
#include "../include/pila.h"


struct rep_pila{
texto_t * stack;
int tope;
int cota;
};


pila crear_pila(const nat tamanio){
  pila p = new rep_pila;
  p->stack= new texto_t[tamanio];
  p->cota = tamanio;
  p->tope = 0;
  return p;
}

void apilar(const texto_t t, pila &p){
if (p->tope<p->cota){
  p->stack[p->tope]=t;
    p->tope++;
  }
}

void desapilar(pila &p){
  if (p->tope>0){
    p->tope--;
  }
}

bool es_vacia_pila(const pila p){
  return p->tope == 0 ;
}

bool es_llena_pila(const pila p){
  return (p->cota == p->tope);
}

texto_t cima(const pila p){
  return p->stack[p->tope-1];
}

void liberar_pila(pila &p){
    int i = 0;
    while (i < p->tope){
        liberar_texto(p->stack[i]);
        i++;
    }
    delete p->stack;
    delete p;
}
