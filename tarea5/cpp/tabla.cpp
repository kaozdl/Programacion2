/* 4580203 - 4660754 */
/*
  Módulo de implementación de `tabla`.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

 #include "../include/info.h"
 #include "../include/lista.h"
#include "../include/tabla.h"
#include "../include/texto.h"

/*
 Hash abierto para identificadores de localidad.
 El nombre de la localidad se almacena en el dato de texto y el identificador
 en el dato numérico de los elementos de la lista.
 */
struct rep_tabla {
  lista *listas;
  nat tamanio;
};

tabla crear_tabla(nat tamanio) {
  tabla res = new rep_tabla;
  res->tamanio = tamanio;
  res->listas = new lista[tamanio];
  for (nat i = 0; i < tamanio; i++)
    res->listas[i] = crear_lista();
  return res;
}

  void insertar_en_tabla(const texto_t clave, int valor, tabla &t) {
    long i = hash_texto(clave,t->tamanio);
    localizador loc = inicio_lista(t->listas[i]);
    insertar_antes(crear_info(valor,copiar_texto(clave)),loc,t->listas[i]);
  }

void insertar_lista_en_tabla(const lista asociaciones, tabla &t) {
  localizador loc = inicio_lista(asociaciones);
  while (es_localizador_lista(loc)) {
    info_t info = info_lista(loc, asociaciones);
    insertar_en_tabla(copiar_texto(texto_info(info)), numero_info(info), t);
    loc = siguiente(loc, asociaciones);
  }
}

void liberar_tabla(tabla &t) {
  for (nat i = 0; i < t->tamanio; i++)
    liberar_lista(t->listas[i]);
  delete[] t->listas;
  delete t;
}

bool valor_en_tabla(texto_t clave, const tabla t, int &n) {
  long i = hash_texto(clave,t->tamanio);
  if (es_vacia_lista(t->listas[i]))
    return false;
  else
    return numero_de_texto(clave,t->listas[i],n);
  return true;
}
