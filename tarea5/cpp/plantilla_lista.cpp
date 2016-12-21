/*
  Módulo de implementación de 'lista'.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#include "../include/lista.h"
#include "../include/texto.h"
#include "../include/info.h"

#include <stddef.h>

struct nodo {
  info_t dato;
  nodo *anterior;
  nodo *siguiente;
};

struct rep_lista {
  nodo *inicio;
  nodo *final;
};

bool numero_de_texto(const texto_t t, const lista lst, int &n) {
  bool res = false;
  localizador loc = inicio_lista(lst);
  while ((!res) && es_localizador_lista(loc)) {
    if (comparar_texto(t, texto_info(info_lista(loc, lst))) == igual) {
      res = true;
      n = numero_info(info_lista(loc, lst));
    } else {
      loc = siguiente(loc, lst);
    }
  }
  return res;
}
