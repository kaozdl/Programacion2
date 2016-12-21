/*
  Módulo de definición de `sistema'.

  Accede a las colecciones de localidades y pedidos.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */
#ifndef _SISTEMA_H
#define _SISTEMA_H

#include "utils.h"
#include "texto.h"
#include "info.h"
#include "lista.h"
#include "localidades.h"

struct rep_sistema; // representación de `sistema', definida en `sistema.cpp'.

typedef rep_sistema *sistema;

/*
  Devuelve el sistema inicializado con sus estructuras de pedidos y localidades
  vacias. Se inicia la fase de ingresar localidades con su grado de urgencia.
 */
sistema iniciar_sistema();

/*
  Libera la memoria asignada a `s' y a sus elementos.
 */
void terminar_sistema(sistema &s);

/*
  Agrega una localidad de nombre `nombre' y urgencia `u' al sistema `s'.
  Si había una localidad con ese nombre actualiza el valor de la urgencia.
 */
void ingresar_localidad(const texto_t nombre, const urgencia_t u, sistema &s);

/*
  Inicia la fase de registro de pedidos con hasta `max_prioridades' para las
  localidades que ya fueron ingresadas al sistema.
  Imprime una lista con todas las localidades en orden lexicográfico creciente
  según su dato de texto. Junto con el nombre se debe imprimir la posición que
  le corresponde en ese orden.
  Ejemplo:
  (1,b)(2,d)(3,e)(4,g)(5,n)(6,p)(7,t)
  Postcondiciones: No se podran agregar mas localidades al sistema.
 */
void iniciar_pedidos(const nat max_prioridades, sistema &s);

/*
  Agrega `detalle' con prioridad `prioridad' a los pedidos para la
  localidad identificada por `localidad` en el sistema `s'.
  Si `localidad` no fue ingresada, no hace nada.
 */
void ingresar_pedido(const texto_t localidad, const info_t detalle,
                     const int prioridad, sistema &s);

/*
  Imprime en orden creciente de rango la sumatoria de todos los montos de
  los pedidos para todas las localidades pertenecientes al rango.
  Es decir, con el siguiente formato:
  70000
  0
  ...
  50000
 */
void imprimir_totales(const sistema s);

/*
  Dado un `rango` imprime un informe de pedidos pertenecientes al sistema `s',
  localidad por localidad en orden lexicografico. Los detalles se deben mostrar
  en orden de prioridad creciente con el formato de (MONTO,NOMBRE).
  No deben quedar pedidos en `s' para el rango `rango'.
  Ejemplo de salida (estando 'Material' asociado a un valor de prioridad menor
  que 'Comida' en Durazno:
  Durazno
   (1100000,Material)(300,Comida)
  Florida

  Tranqueras
   (10000,Material)

  Precondición 1 <= rango <= 5.
 */
void procesar_rango(rango_t rango, sistema &s);

#endif
