/* 4580203 - 4660754 */
#include "../include/utils.h"
#include "../include/texto.h"
#include "../include/info.h"
#include "../include/lista.h"
#include "../include/pedidos.h"
#include "../include/cola_de_prioridad.h"
#include "../include/tabla.h"
#include <stdlib.h>

struct rep_pedidos {
cola_de_prioridad *c;
lista locs;
nat cantidad_localidades;
tabla tab;
};

pedidos crear_pedidos(const nat cant_loc, const lista enum_loc, const nat max_prioridades){
  pedidos p = new rep_pedidos;
  p->cantidad_localidades = cant_loc;
  p->locs = enum_loc;
  p->c = new cola_de_prioridad[cant_loc+1];
  for (nat i = 1;i<=cant_loc;i++) p->c[i] = crear_cp(max_prioridades);
  p->tab = crear_tabla(cant_loc);
  return p;
}

void agregar_pedido(const texto_t localidad, const info_t detalle, const int prioridad, pedidos &p){
  int n;
  if (!(valor_en_tabla(localidad , p->tab, n)))
    insertar_en_tabla(localidad, numero_info(detalle), p->tab);
  else
    insertar_en_tabla(localidad, numero_info(detalle)+n, p->tab);
  int m;
  if (numero_de_texto(localidad,p->locs, m))
    insertar_en_cp(detalle, prioridad, p->c[m]);
}

void liberar_pedidos(pedidos &p){
  if (p!=NULL){
    for (nat i = 1; i<=p->cantidad_localidades; i++)
      liberar_cp (p->c[i]);
    liberar_tabla(p->tab);
    liberar_lista(p->locs);
    delete p;
  }
}

lista listar_detalles_prioritarios(const texto_t localidad, const pedidos p){
  int num;
  lista lst = crear_lista();
  if (!numero_de_texto(localidad,p->locs, num))
    return lst;
  else{
    nat prioridad = valor_prioritario(p->c[num]);
    return lista_en_cp(prioridad, p->c[num]);
  }
}

nat total_monto(const texto_t localidad, const pedidos p){
  if (p == NULL)
    return 0;
  else{
    int n = 0;
    if (valor_en_tabla(localidad,p->tab,n))
      return n;
    else
      return n;
   }
}


lista procesar_localidad(const texto_t localidad, pedidos &p){
  lista lst = crear_lista();
  localizador loc;
  int i;
  if (p!=NULL && numero_de_texto(localidad,p->locs,i))
    for (int n = i; !es_vacia_cp(p->c[n]); eliminar_prioritario(p->c[n])) {
      insertar_despues(prioritario(p->c[n]),loc,lst);
      insertar_en_tabla(localidad,0,p->tab);
      loc = final_lista(lst);
    }
  return lst;
}
