/* 4580203 - 4660754 */
#include "../include/utils.h"
#include "../include/texto.h"
#include "../include/info.h"
#include "../include/lista.h"
#include "../include/binario.h"
#include "../include/pila.h"
#include "../include/cola_binarios.h"
#include "../include/conjunto.h"
#include "../include/cola_de_prioridad.h"

#include <stdlib.h>


struct nodo {
  binario dato;
  nodo *siguiente;
};

struct rep_cola_binarios {
  nodo *inicio;
  nodo *final;
};

typedef rep_cola_binarios *cola_binarios;

cola_binarios crear_cola_binarios(){
  cola_binarios cb = new rep_cola_binarios;
  cb->inicio = NULL;
  cb->final = NULL;
  return cb;
}

void encolar(const binario b, cola_binarios &c){
      nodo *n = new nodo;
      n->dato = b;
      n->siguiente = NULL;
      if (c->final != NULL){
      c->final->siguiente = n;
      c->final = n;
    }
    else{
        c->inicio = n;
        c->final = n;
    }
}

void desencolar(cola_binarios &c){
  if (!es_vacia_cola_binarios(c)){
    c->inicio = c->inicio->siguiente;
  }
  if (c->inicio==NULL)
      c->final=NULL;
}

bool es_vacia_cola_binarios(const cola_binarios c){
  return (c->inicio == NULL);
}

binario frente(const cola_binarios c){
  return c->inicio->dato;
}

void liberar_cola_binarios(cola_binarios &c){
  delete c;
}
