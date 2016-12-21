/* 4580203 - 4660754 */
/*
  Módulo de implementación de 'lista'.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#include "../include/lista.h"
#include "../include/info.h"

#include <stddef.h>

// nodo con punteros al anterior y al siguiente
struct nodo {
  info_t dato;
  nodo *anterior;   nodo *siguiente;
};

// lista implementada con cabecera con punteros al incio y al final
struct rep_lista {
  nodo *inicio;
  nodo *final;
};

lista crear_lista() {
  // se obtiene espacio para la cabecera
  // la lista vacía no es NULL
  lista segmento = new rep_lista;
  segmento->inicio = segmento->final = NULL;
  return segmento;
}

void insertar_antes(const info_t i, const localizador loc, lista &lst) {
  nodo *nuevo = new nodo;
  nuevo->dato = i;
  if (es_vacia_lista(lst)) {
    // nuevo es el único nodo, por lo que es el inicio y el final
    lst->inicio = lst->final = nuevo;
    nuevo->anterior = nuevo->siguiente = NULL;
  } else {
    nuevo->siguiente = loc;
    nuevo->anterior = loc->anterior;
    loc->anterior = nuevo;

    if (loc == lst->inicio)
      lst->inicio = nuevo;
    else
      nuevo->anterior->siguiente = nuevo;
  }
}

lista segmento_lista(const localizador desde, const localizador hasta,
                     const lista lst) {
  lista segmento = crear_lista();
  if (!es_vacia_lista(lst)) {
    localizador loc = desde;
    while (loc != hasta->siguiente) {
      // ERROR: compartiría memoria
      // info_t info = loc->dato;

      // ERROR: compartiría memoria
      // info_t info = crear_info(numero_info(loc->dato),
      // texto_info(loc->dato));

      info_t info = crear_info(numero_info(loc->dato),
                               copiar_texto(texto_info(loc->dato)));
      insertar_despues(info, final_lista(segmento), segmento);
      loc = siguiente(loc, lst);
    }
  }
  return segmento;
}

bool es_localizador_lista(const localizador loc) { return loc != NULL; }

bool localizador_pertenece_a_lista(const localizador loc, const lista lst) {
  bool segmento = false;
  localizador cursor = lst->inicio;
  while ((!segmento) && (es_localizador_lista(cursor))) {
    if (cursor == loc)
      segmento = true;     else
      cursor = cursor->siguiente;
  }
  return segmento;
}

localizador siguiente_clave(const int clave, const localizador loc,
                            const lista lst) {
  localizador segmento;
  if (es_vacia_lista(lst))
    segmento = NULL;
  else {
    segmento = loc;
    bool encontrado = false;
    while ((!encontrado) && (segmento != NULL)) {
      if (numero_info(segmento->dato) == clave)
        encontrado = true;
      else
        segmento = segmento->siguiente;
    }
  }
  return segmento;
}

void mover_antes(localizador loc1, localizador loc2, lista &lst) {
  // En esta versión no se solicita memoria para crear nodos, sino que
  // se mueve todo el nodo que es accedido con `loc2`.
  if (loc1 != loc2) {
    // La creación de una lista requiere espacio para la cabecera que habrá
    // que liberar al final.
    lista sgm = separar_segmento(loc2, loc2, lst);

    // El segemento (de un elemento) se inserta antes de `loc1`.
    // Es lo que se haría si existiera la funcióm insertar_segmento_antes
    // excepto en que acá no es necesario contemplar el caso en que la lista
    // es vacía ya que se sabe que loc1 != loc2
    sgm->inicio->anterior = loc1->anterior;
    sgm->final->siguiente = loc1;
    if (es_inicio_lista(loc1, lst)) {
      lst->inicio = sgm->inicio;
    } else {
      loc1->anterior->siguiente = sgm->inicio;
    }
    loc1->anterior = sgm->final;

    // Se libera la memoria de la cabecera de la lista, ya vacía.
    delete sgm;
  }
}


void insertar_despues(const info_t i, const localizador loc, lista &lst) {
  nodo *nuevo = new nodo;
  nuevo->dato = i;
  nuevo->siguiente = NULL;
  nuevo->anterior = NULL;
  if (es_vacia_lista(lst)) {
	   lst->inicio = lst->final = nuevo;
      	}
	else{
    if (loc != lst->final){
      loc->siguiente->anterior = nuevo;
      nuevo->siguiente = loc->siguiente;
      nuevo->anterior = loc;
      loc->siguiente = nuevo;
    }
    else {
      loc->siguiente = nuevo;
      nuevo->anterior = loc;
      lst->final = nuevo;
    }
  }
}

void insertar_segmento_despues(lista &sgm, const localizador loc, lista &lst) {
  if (es_vacia_lista (lst) && (!es_vacia_lista(sgm))){
    lst->inicio = sgm->inicio;
    lst->final = sgm->final;
  }
  else if ((loc->siguiente != NULL) && (!es_vacia_lista(sgm))) {
    localizador resto = loc->siguiente;
    loc->siguiente = sgm->inicio;
    sgm->final->siguiente = resto;
    resto->anterior = sgm->final;
    sgm->inicio->anterior = loc;
  }
      else if (!es_vacia_lista(sgm)) {
        loc->siguiente = sgm->inicio;
        sgm->inicio->anterior = loc;
        lst->final = sgm->final;

  }
  sgm->inicio = NULL;
  sgm->final = NULL;
}

lista separar_segmento(localizador desde, localizador hasta, lista &lst) {
    lista segmento = crear_lista();
    if (lst->inicio!=NULL){
        segmento->inicio = desde;
        segmento->final = hasta;
        if (segmento->final->siguiente!=NULL)
            segmento->final->siguiente->anterior = desde->anterior;
        else
            lst->final=desde->anterior;
        if (segmento->inicio->anterior !=NULL)
            segmento->inicio->anterior->siguiente = hasta->siguiente;
        else
            lst->inicio=hasta->siguiente;
        desde->anterior=NULL;
        hasta->siguiente=NULL;
    }
    return segmento;
}

void remover_de_lista(localizador &loc, lista &lst) {
if (!es_vacia_lista(lst)){
    if (es_localizador_lista(loc->siguiente))
        loc->siguiente->anterior= loc->anterior;
    else
        lst->final=loc->anterior;
    if (es_localizador_lista(loc->anterior))
            loc->anterior->siguiente = loc->siguiente;
    else
        lst->inicio = loc->siguiente;
      delete loc;
    }
}

void liberar_lista(lista &lst) {
  localizador loc = lst->final;
  while (loc!=NULL){
    localizador anterior = loc->anterior;
    delete loc;
    loc = anterior;
  }
  delete lst;
  lst=NULL;
}

bool es_vacia_lista(const lista lst) {
  return (lst->inicio==NULL);
}

bool es_inicio_lista(const localizador loc, const lista lst) {
  return (loc==lst->inicio);
}

bool es_final_lista(const localizador loc, const lista lst) {
  return (loc==lst->final);
}

localizador inicio_lista(const lista lst) {
  return lst->inicio;
}

localizador final_lista(const lista lst) {
  return lst->final;
}

localizador siguiente(const localizador loc, const lista lst) {
  return loc->siguiente;
}

localizador anterior(const localizador loc, const lista lst) {
  return loc->anterior;
}

bool precede_en_lista(const localizador l1, const localizador l2,const lista lst) {
  localizador localizador1 = l2;
  while (es_localizador_lista(localizador1) && localizador1!=l1)
    localizador1=anterior(localizador1,lst);
  return es_localizador_lista(localizador1);
}

localizador anterior_clave(const int clave, const localizador loc,const lista lst) {
  localizador localizador1 = loc;
  if(es_localizador_lista(localizador1)){
    while (es_localizador_lista(localizador1) && numero_info(info_lista(localizador1,lst))!=clave)
      localizador1 =anterior(localizador1,lst);
      return localizador1;
    }
  else return NULL;
}

info_t info_lista(const localizador loc, const lista lst) {
  return loc->dato;
}

void cambiar_en_lista(const info_t i, const localizador loc, lista &lst) {
  loc->dato=i;
}

void intercambiar(const localizador loc1, const localizador loc2, lista &lst) {
  info_t info_auxiliar = loc1->dato;
  loc1->dato = loc2->dato;
  loc2->dato = info_auxiliar;
}
