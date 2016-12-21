/* 4580203 - 4660754 */
#include "../include/utils.h"
#include "../include/texto.h"
#include "../include/info.h"
#include "../include/lista.h"
#include "../include/binario.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

struct rep_binario {
  info_t dato;
  rep_binario *izq;
  rep_binario *der;
};
nat max (const nat a, const nat b){
  if (a < b) return b;
  else return a;
}

bool Es_Hoja(const binario b){
  return ((b->der == NULL) && (b->izq == NULL));
}

binario crear_binario() {
  binario b = NULL;
  return b;
}

bool insertar_en_binario(const info_t i, binario &b) {
    if (b==NULL){
        b= new rep_binario;
        b->dato =i;
        b->izq=NULL;
        b->der=NULL;
        return true;
    }
    else if (comparar_texto(texto_info(i),texto_info(b->dato))==mayor)
             return insertar_en_binario(i,b->der);
    else if (comparar_texto(texto_info(i),texto_info(b->dato))==menor)
             return insertar_en_binario(i,b->izq);
    else
        return false;
  }


info_t remover_mayor(binario &b) {
  info_t res;
  if (b->der == NULL) {
    res = b->dato;
    binario izq = b->izq;
    delete (b);
    b = izq;
  } else {
    res = remover_mayor(b->der);
  }
  return res;
}

binario crear_filtrado(const int clave, comp_t criterio, const binario b) {
  if (b == NULL)
    return NULL;
  else {
    binario fizq = crear_filtrado(clave,criterio,b->izq);
    binario fder = crear_filtrado(clave,criterio,b->der);
    if (criterio == menor){
      if (clave > numero_info(b->dato)){
        binario fil = new rep_binario;
        fil->dato = crear_info(numero_info(b->dato), copiar_texto(texto_info(b->dato)));
        fil->izq = fizq;
        fil->der = fder;
        return fil;
      }
      else if (es_vacio_binario(fizq)){
        return fder;
      }
      else if (es_vacio_binario(fder)){
        return fizq;
      }
      else {
        info_t mayor = remover_mayor(fizq);
        binario fil = new rep_binario;
        fil->dato = crear_info(numero_info(mayor), copiar_texto(texto_info(mayor)));
        fil->izq = fizq;
        fil->der = fder;
        return fil;
      }
    }
    else if (criterio == mayor){
      if (clave < numero_info(b->dato)){
        binario fil = new rep_binario;
        fil->dato = crear_info(numero_info(b->dato), copiar_texto(texto_info(b->dato)));
        fil->izq = fizq;
        fil->der = fder;
        return fil;
      }
      else if (es_vacio_binario(fizq)){
        return fder;
      }
      else if (es_vacio_binario(fder)){
        return fizq;
      }
      else {
        info_t mayor = remover_mayor(fizq);
        binario fil = new rep_binario;
        fil->dato = crear_info(numero_info(mayor), copiar_texto(texto_info(mayor)));
        fil->izq = fizq;
        fil->der = fder;
        return fil;
      }
    }
    else {
      if (clave == numero_info(b->dato)){
        binario fil = new rep_binario;
        fil->dato = crear_info(numero_info(b->dato), copiar_texto(texto_info(b->dato)));
        fil->izq = fizq;
        fil->der = fder;
        return fil;
      }
      else if (es_vacio_binario(fizq)){
        return fder;
      }
      else if (es_vacio_binario(fder)){
        return fizq;
      }
      else {
        info_t mayor = remover_mayor(fizq);
        binario fil = new rep_binario;
        fil->dato = crear_info(numero_info(mayor), copiar_texto(texto_info(mayor)));
        fil->izq = fizq;
        fil->der = fder;
        return fil;
      }
    }

  }

}




void remover_de_binario(const texto_t t, binario &b) {
  if (b != NULL){
    if (comparar_texto(t,texto_info(b->dato))==menor)
      remover_de_binario(t,b->izq);
    if (comparar_texto(t,texto_info(b->dato))==mayor)
      remover_de_binario(t,b->der);
    if (comparar_texto(t,texto_info(b->dato))==igual){
      if (b->izq == NULL){
        binario borrar = b;
        b = b->der;
        delete borrar;
      }
     else if (b->der == NULL){
       binario borrar = b;
       b = b->izq;
       delete borrar;
     }
     else{

       b->dato=remover_mayor(b->izq);
     }
    }
  }
}

void liberar_binario(binario &b) {
  if (b!=NULL){
    liberar_binario(b->izq);
    liberar_binario(b->der);
    liberar_info(b->dato);
    }
}

bool es_vacio_binario(const binario b) {
  return b == NULL;
}

info_t raiz_binario(const binario b) {
  return b->dato;
}

binario izquierdo(const binario b) {
  return b->izq;
}

binario derecho(const binario b) {
  return b->der;
}

binario buscar_subarbol(const texto_t t, const binario b) {
  if (b == NULL)
    return b;
  else{
    if (comparar_texto(texto_info(b->dato),t)==menor)
      return buscar_subarbol(t,b->der);
    else if (comparar_texto(texto_info(b->dato),t)==mayor)
      return buscar_subarbol(t,b->izq);
    else
      return b;
  }
}

nat altura_binario(const binario b) {
  if (es_vacio_binario(b))
   return 0;
  else
   return (1+max(altura_binario(b->izq),altura_binario(b->der)));
  }


nat cantidad_binario(const binario b) {
  if (b == NULL)
    return 0;
  else
    return 1 + cantidad_binario(b->izq) + cantidad_binario(b->der);
}

nat cantidad_de_caminos_aux(localizador loc, const lista l, const binario b){
  if (!es_localizador_lista(loc) || es_vacio_binario(b))  {
    return 0;
  }
  else if (numero_info(info_lista(loc,l)) != numero_info(b->dato))
    return 0;
      else{
    if(Es_Hoja(b) && es_final_lista(loc,l))
      return 1;
    else{
      loc = siguiente(loc,l);
      return cantidad_de_caminos_aux(loc,l,derecho(b))+cantidad_de_caminos_aux(loc,l,izquierdo(b));
    }
  }

}

nat cantidad_de_caminos(const lista l, const binario b) {
  localizador aux = inicio_lista(l);
  nat cantidad = cantidad_de_caminos_aux(aux,l,b);
  return cantidad;
}

/*
  Auxiliar para camino_a_texto.
 */
static void agregar_rama(char *cadena, rama_t r) {
  switch (r) {
  case izq:
    strcat(cadena, "I");
    break;
  case der:
    strcat(cadena, "D");
    break;
  }
}

texto_t camino_a_texto(const camino_t c) {
  texto_t res;
  // espacio suficiente para "No existe" o para cada rama y la coma y la
  // cantidad, el guión y los paréntesis.
  char cadena[c.cantidad_ramas * 2 + 10];
  if (!c.existe) {
    strcpy(cadena, "No existe");
  } else {
    sprintf(cadena, "%d", c.cantidad_ramas);
    strcat(cadena, "-(");
    if (c.cantidad_ramas > 0) {
      agregar_rama(cadena, c.ramas[0]);
      for (nat i = 1; i < c.cantidad_ramas; i++) {
        strcat(cadena, ",");
        agregar_rama(cadena, c.ramas[i]);
      }
    }
    strcat(cadena, ")");
  }
  res = cadena_a_texto(cadena);
  return res;
}

void buscar_camino_aux(const lista l,localizador loc ,const binario b , camino_t & camino) {
    if (!es_localizador_lista(loc)||es_vacio_binario(b))
        camino.existe=false;
    else if (comparar_texto(texto_info(info_lista(loc,l)),texto_info(b->dato))!=igual)
        camino.existe = false;
    else{
      localizador sig = siguiente(loc,l);
      if (b->izq!=NULL && b->der!=NULL) {
      camino.ramas[camino.cantidad_ramas]=der;
      camino.cantidad_ramas++;
      camino.existe = true;
      buscar_camino_aux(l,sig,derecho(b),camino);
      if (!camino.existe){
        camino.ramas[camino.cantidad_ramas-1]=izq;
        camino.existe = true;
        buscar_camino_aux(l,sig,izquierdo(b),camino);
      }
    }
      else if (b->izq==NULL && b->der!=NULL) {
        camino.ramas[camino.cantidad_ramas]=der;
        camino.cantidad_ramas++;
        camino.existe = true;
        buscar_camino_aux(l,sig,derecho(b),camino);
        if (!camino.existe){
          camino.ramas[camino.cantidad_ramas-1]=izq;
          camino.existe = true;
          buscar_camino_aux(l,sig,izquierdo(b),camino);
        }
      }
      else if (b->izq!=NULL && b->der==NULL) {
        camino.ramas[camino.cantidad_ramas]=izq;
        camino.cantidad_ramas++;
        camino.existe = true;
        buscar_camino_aux(l,sig,izquierdo(b),camino);
        if (!camino.existe){
        camino.ramas[camino.cantidad_ramas-1]=der;
        camino.existe = true;
        buscar_camino_aux(l,sig,derecho(b),camino);
      }
    }
    else if (b->izq==NULL && b->der!=NULL) {
      camino.ramas[camino.cantidad_ramas]=der;
      camino.cantidad_ramas++;
      camino.existe = true;
      buscar_camino_aux(l,sig,derecho(b),camino);
      if (!camino.existe){
        camino.ramas[camino.cantidad_ramas-1]=izq;
        camino.existe = true;
        buscar_camino_aux(l,sig,izquierdo(b),camino);
      }
    }
    else{
        if (es_localizador_lista(sig))
            camino.existe=false;
    }
    }
}
camino_t buscar_camino(const lista l, const binario b) {
        camino_t camino;
        camino.existe = true;
        camino.ramas = new rama_t[altura_binario(b)-1];
        camino.cantidad_ramas=0;
        localizador loc = inicio_lista(l);
        buscar_camino_aux(l,loc,b,camino);
        return camino;
}


void imprimir_binario_auxiliar (const nat k, const binario b){
  if (b != NULL) {
    imprimir_binario_auxiliar(k+1, b->der);
    for (nat i = 0; i < k; i++)
      printf("-");
    escribir_texto(info_a_texto(b->dato));
    printf("\n");
    imprimir_binario_auxiliar (k+1,b->izq);
  }
}

void imprimir_binario(const binario b) {
if (b != NULL){
  int k = 0;
  imprimir_binario_auxiliar(k,b);
  }
}
