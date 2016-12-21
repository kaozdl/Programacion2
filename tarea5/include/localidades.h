/*
  Módulo de definición de localidades.

  Se mantiene el conjunto de localidades.
  Una localidad se representa por su nombre, que es un elemento de tipo
  `texto_t`. Cada localidad tiene asignada una urgencia que es un valor entero
  entre 1 y 100, incluidos.
  Las urgencias se clasifican en 5 rangos, identificados desde el 1 al 5. Al
  rango `i` le corresponden las urgencias en el intervalo
  [20 * (i-1) + 1, 20 * i].
  Es decir que los rangos son:
     Rango 1: [1, 20]
     Rango 2: [21, 40]
     Rango 3: [41, 60]
     Rango 4: [61, 80]
     Rango 5: [81, 100]

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _LOCALIDADES_H
#define _LOCALIDADES_H

#include "utils.h"
#include "texto.h"
#include "lista.h"
#include "conjunto.h"

/*
  Tipo para el nivel de urgencia.
  Debe valer entre 1 y 100.
 */
typedef nat urgencia_t;

/*
  Tipo para el rango de urgencia.
  Debe valer entre 1 y 5.
 */
typedef nat rango_t;

/*
 Representación de `localidades', definida en `localidades.cpp'.
 */
struct rep_localidades;
typedef rep_localidades *localidades;

/*
  Devuelve una estructura vacía (sin elementos) para mantener localidades.
 */
localidades crear_localidades();

/*
  Agrega a `l' la localidad `nombre' a la que se le asigna urgencia `u'.
  Si en `l' ya estaba `nombre', se remueve y se agrega con la nueva urgencia.
  Precondición: 1 <= u <= 100.
 */
void agregar_localidad(const texto_t nombre, const urgencia_t u,
                       localidades &l);

/*
  Devuelve la cantidad de localidades en `l'.
 */
nat cantidad_localidades(const localidades l);

/*
  Devuelve la urgencia asignada a `nombre' en `l',
  Si en `l' no existe esa localidad devuelve 0.
 */
urgencia_t urgencia(const texto_t nombre, const localidades l);

/*
  Devuelve una lista con los nombres de las localidades de `l' cuya urgencia
  pertence a `rango'.
  La lista resultado debe estar en orden lexicográfico creciente según su dato
  de texto. El dato numérico de los elementos de la lista debe ser la posición
  que en orden lexicográfico creciente le corresponde al dato de texto en `l',
  correspondiéndole la posición 1 al primer elemento.
  La lista resultado no comparte memoria con `l'.
  Precondición: 1 <= rango <= 5.
  Ejemplo: Sea `l` tal que su conjunto de localidades es:
  {(Artigas,40), (Dolores,100), (Melo,41), (Punta del Este,9), (San José,81)}
  Para cada rango se debe devolver:
  1:[(Punta del Este,4)]
  2:[(Artigas,1)]
  3:[(Melo,3)]
  4:[]
  5:[(Dolores,2), (San José,5)]
 */
lista listar_rango(const rango_t rango, const localidades l);

/*
  Devuelve una lista con las localidades de `l' cuyos nombres pertenecen a `c'.
  La lista resultado debe estar en orden lexicográfico creciente según su dato
  de texto. El dato numérico de los elementos de la lista debe ser la posición
  que en orden lexicográfico creciente le corresponde al dato de texto en `l',
  correspondiéndole la posición 1 al primer elemento.
  Ejemplo: Sea `l' tal que su conjunto de localidades es:
  {(Artigas,40), (Dolores,100), (Melo,41), (Punta del Este,9), (San José,81)}

  Si `c` es {(San José,140), (Paysandú,45), (Artigas,0)}
  se debe devolver
  [(Artigas,1), (San José,5)]

  Si `c` es {(Paysandú,45), (Rivera,70)}
  se debe devolver
  []
 */
lista pertenecen(const conjunto c, const localidades l);

/*
  Devuelve una lista con las localidades de `l'.
  La lista resultado debe estar en orden lexicográfico creciente según su dato
  de texto. El dato numérico de los elementos de la lista debe ser la posición
  que en orden lexicográfico creciente le corresponde al dato de texto en `l',
  correspondiéndole la posición 1 al primer elemento.
  La lista resultado no comparte memoria con `l'.
 */
lista listar_todos(const localidades l);

/*
 Libera la memoria asignada a `l' y a todos sus elementos.
 */
void liberar_localidades(localidades &l);

#endif
