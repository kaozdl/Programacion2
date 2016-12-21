/* 4580203 - 4660754 */
#include "../include/utils.h"
#include "../include/texto.h"
#include "../include/lista.h"
#include "../include/conjunto.h"
#include "../include/localidades.h"
#include "../include/binario.h"
#include <stdlib.h>

typedef nat urgencia_t;

typedef nat rango_t;

struct rep_localidades{
    binario bin;
};

localidades crear_localidades(){
  localidades loc = new rep_localidades;
  loc->bin = crear_binario();
  return loc;
 }

void agregar_localidad(const texto_t nombre, const urgencia_t u, localidades &l){
  info_t info = crear_info(u,nombre);
  insertar_en_binario(info,l->bin);
}

nat cantidad_localidades(const localidades l){
  return cantidad_binario(l->bin);
}

urgencia_t urgencia(const texto_t nombre, const localidades l){
  return numero_info(raiz_binario(buscar_subarbol(nombre,l->bin)));
}

lista listar_rango(const rango_t rango, const localidades l){
  binario bin = crear_binario();
  binario bin2 = crear_binario();
  if (rango == 1){
    bin = crear_filtrado(0,mayor,l->bin);
    bin2 = crear_filtrado(21,menor,bin);
  }
  else if (rango == 2){
    bin = crear_filtrado(20,mayor,l->bin);
    bin2 = crear_filtrado(41,menor,bin);
  }
  else if (rango == 3){
    bin = crear_filtrado(40,mayor,l->bin);
    bin2 = crear_filtrado(61,menor,bin);
  }
  else if (rango == 4){
    bin = crear_filtrado(60,mayor,l->bin);
    bin2 = crear_filtrado(81,menor,bin);
  }
  else{
    bin = crear_filtrado(80,mayor,l->bin);
    bin2 = crear_filtrado(101,menor,bin);
  }
  lista lst = linealizacion(bin2);
  return lst;
}

lista pertenecen(const conjunto c, const localidades l){
  lista res = crear_lista();
  localizador resins = inicio_lista(res);
  lista lst = linealizacion(l->bin);
  localizador loc = inicio_lista(lst);
  while (es_localizador_lista(loc)){
    if ( pertenece(texto_info(info_lista(loc,lst)),c)){
      insertar_despues(info_lista(loc,lst),resins, res);
      resins = siguiente (resins,res);
    }
    loc=siguiente(loc,lst);
  }
  return res;
}

lista listar_todos(const localidades l){
  lista l1 = linealizacion(l->bin);
  localizador loc =inicio_lista(l1);
  lista lst=crear_lista();
  localizador loc1 = inicio_lista(lst);
  for (nat i = 1; es_localizador_lista(loc);i++) {
    insertar_despues(crear_info(i,copiar_texto(texto_info(info_lista(loc,l1)))),loc1,lst);
    loc1 = final_lista(lst);
    loc = siguiente(loc,l1);
  }
  return lst;
}

void liberar_localidades(localidades &l){
  liberar_binario(l->bin);
  delete l;
}
