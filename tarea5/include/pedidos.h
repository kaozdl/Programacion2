/*
  Módulo de definición de `pedidos'.

  Mantiene la estructura de los `pedidos' que se hacen para las localidades.
  El conjunto de localidades es conocido y su cantidad es `cant_loc'.

  Cada pedido consiste en un detalle compuesto por un texto que representa el
  insumo y un entero (no negativo) que representa el monto (costo). A cada
  pedido se le asigna un valor que determina su orden de prioridad. El pedido es
  asignado a una localidad. Estos valores son enteros entre 1 y
  `max_prioridades'.
  Los valores de `cant_loc' y `max_prioridades' son establecidos por los
  parámetros pasados en el constructor `crear_pedidos'.


  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _PEDIDOS_H
#define _PEDIDOS_H

#include "utils.h"
#include "texto.h"
#include "info.h"
#include "lista.h"

struct rep_pedidos; // representación de `pedidos', definida en `pedidos.cpp'.

typedef rep_pedidos *pedidos;

/*
  Devuelve una estructura para mantener los pedidos. Los valores que determinan
  la prioridad están entre 1 y `max_prioridades'.
  En `enum_loc` se listan las `cant_loc' localidades para las cuales se reciben
  pedidos. La lista está en orden lexicográfico creciente de su dato de texto.
  El dato numérico de los elementos de `enum_loc' es la posición que en ese
  orden le corresponde a la localidad, correspondiéndole la posición 1 al
  primer elemento.
 */
pedidos crear_pedidos(const nat cant_loc, const lista enum_loc,
                      const nat max_prioridades);

/*
  Agrega `detalle' con prioridad determinada por `prioridad' a los pedidos para
  `localidad'.
  Si `localidad' no fue ingresada en `crear_pedidos' no hace nada.
  Precondiciones:
  1 <= prioridad <= max_prioridades
  numero_info(detalle) > 0
 */
void agregar_pedido(const texto_t localidad, const info_t detalle,
                    const int prioridad, pedidos &p);

/*
  Libera la memoria asignada a `p' y a sus elementos.
 */
void liberar_pedidos(pedidos &p);

/*
  Devuelve la lista con los detalles de los pedidos para `localidad' que están
  asociados al mínimo valor de prioridad de los pedidos hechos para esa
  localidad. La lista debe estar en orden cronológico creciente del tiempo en
  que los detalles fueron agregados.
  Si `localidad' no fue ingresada en `crear_pedidos' devuelve una lista vacía.
  El tiempo de ejecución es O(1) en promedio.
  La lista devuelta comparte memoria con `p'.
 */
lista listar_detalles_prioritarios(const texto_t localidad, const pedidos p);

/*
  Devuelve el total de los costos de todos los pedidos para `localidad'.
  Si `localidad' no fue ingresada en `crear_pedidos' devuelve 0.
  El tiempo de ejecución es O(1) en promedio.
 */
nat total_monto(const texto_t localidad, const pedidos p);

/*
  Devuelve una lista con todos los detalles de todos los pedidos para
  `localidad'. La lista debe estar ordenada de manera
  creciente por la prioridad, y entre los que tengan igual prioridad en orden
  cronológico creciente del tiempo en que los detalles fueron agregados.

  El tiempo de ejecución es
  O(cant_pedidos + max_prioridad X log (max_prioridad)) en promedio.
  donde `cant_pedidos' es la cantidad de pedidos para `localidad'.
  No deben quedar pedidos en `p` para `localidad'.
 */
lista procesar_localidad(const texto_t localidad, pedidos &p);

#endif
