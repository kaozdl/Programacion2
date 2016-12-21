/* 4580203 - 4660754 */
#include "../include/utils.h"
#include "../include/texto.h"
#include "../include/info.h"
#include "../include/lista.h"
#include "../include/binario.h"

#include "../include/conjunto.h"
#include "../include/cola_de_prioridad.h"

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

binario kesimo_subarbol(const nat k, const binario b) {
  nat cant_sub_izq = cantidad_binario(izquierdo(b));
  if (k==cant_sub_izq+1)
    return b;
  else if (k>cant_sub_izq+1)
    return kesimo_subarbol(k-cant_sub_izq-1,derecho(b));
  else
    return kesimo_subarbol(k,izquierdo(b));
}

binario crear_balanceado_aux(const lista lst, localizador & loc, const int ini, const int fin){
  if (ini>fin)
    return crear_binario();
  else{
    int mid = ini +(fin-ini+1)/2;
    binario izq=crear_balanceado_aux(lst,loc,ini,mid-1);
    binario b = new rep_binario;
    info_t info = info_lista(loc,lst);
    b->dato = copiar_info(info);
    b->izq =izq;
    loc=siguiente(loc,lst);
    b->der = crear_balanceado_aux(lst,loc,mid+1,fin);
    return b;
  }
}

int largo_lista(const lista lst){
  int largo = 0;
  localizador localizador1 = inicio_lista(lst);
  while(es_localizador_lista(localizador1)){
    largo ++;
    localizador1=siguiente(localizador1,lst);
  }
  return largo;
}

binario crear_balanceado(const lista lst){
  binario b = crear_binario();
  if (!es_vacia_lista(lst)){
    localizador localizador1 = inicio_lista(lst);
    int largo = largo_lista(lst);
    b=crear_balanceado_aux(lst,localizador1,0,largo-1);
  }
  return b;
}


void linealizacion_aux(const binario b, lista & l, localizador & loc){
  if (!es_vacio_binario(b)){
    if (!es_vacio_binario(izquierdo(b))){
      linealizacion_aux(b->izq,l,loc);
      loc=final_lista(l);
    }
    else l=crear_lista();
    info_t info = b->dato;
    insertar_despues(copiar_info(info),loc,l);
    if (!es_vacio_binario(derecho(b))){
      lista lst1;
      localizador localizador1;
      linealizacion_aux(b->der,lst1,localizador1);
      loc=final_lista(l);
      insertar_segmento_despues(lst1,loc,l);
    }
  }
  else
    l=crear_lista();
}

lista linealizacion(const binario b){
  lista lin =crear_lista();
  localizador loc;
  linealizacion_aux(b,lin,loc);
  return lin;
}
