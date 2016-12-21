/* 4580203 - 4660754 */
#include <localidades.h>
#include <lista.h>
#include <info.h>
#include <utils.h>
#include <texto.h>
#include <pedidos.h>
#include <stdio.h>
#include <stdlib.h>


struct rep_sistema{
    localidades l;
    pedidos p;
};

typedef rep_sistema *sistema;

sistema iniciar_sistema(){
  sistema s = new rep_sistema;
  s->l = crear_localidades();
  s->p = NULL;
  return s;
}

void terminar_sistema(sistema &s){
  liberar_localidades(s->l);
  liberar_pedidos(s->p);
  delete s;
}

void ingresar_localidad(const texto_t nombre, const urgencia_t u, sistema &s){
  agregar_localidad(nombre, u,s->l);
}

void iniciar_pedidos(const nat max_prioridades, sistema &s){
  imprimir_lista(listar_todos(s->l));
  s->p = crear_pedidos(cantidad_localidades(s->l),listar_todos(s->l),max_prioridades);
}

void ingresar_pedido(const texto_t localidad, const info_t detalle, const int prioridad, sistema &s){
  agregar_pedido(localidad,detalle,prioridad,s->p);
}

void imprimir_totales(const sistema s){
  rango_t i = 1;
  while (i < 6) {
    lista l = listar_rango(i,s->l);
    localizador loc = inicio_lista(l);
    int cont = 0;
    while (es_localizador_lista(loc)){
      cont = cont + total_monto(texto_info(info_lista(loc,l)),s->p);
      loc = siguiente(loc,l);
    }
    printf("%d\n",cont);
    i++;
  }
}

void procesar_rango(rango_t rango,sistema &s){
  lista locals = listar_rango(rango, s->l);
  localizador avance = inicio_lista(locals);
  while (es_localizador_lista(avance)) {
    escribir_texto(texto_info(info_lista(avance,locals)));
    printf("\n");
    lista datos = procesar_localidad(texto_info(info_lista(avance,locals)),s->p);
    imprimir_lista(datos);
    avance = siguiente(avance,locals);
  }
}
