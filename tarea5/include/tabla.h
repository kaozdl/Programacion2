/*
  Módulo de definición de `tabla'.

  Se define una tabla acotada de asociaciones de texto a número.
  La cantidad máxima de asociaciones queda determinada por el parámetro
  `tamanio` pasado en `crear_tabla'.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#include "../include/texto.h"
#include "../include/lista.h"

struct rep_tabla; // representación de `tabla', definida en `tabla.cpp'.

typedef rep_tabla *tabla;

/*
 Crea una tabla de asociaciones texto->numero.
 Podrá haber hasta `tamanio` asociaciones.
 */
tabla crear_tabla(nat tamanio);

/*
  Inserta en `t` la asociación entre `clave' y `valor'.
  Si ya existía una asociación para `clave' es reemplazada por la
  nueva.
  El tiempo de ejecución es O(1).
 */
void insertar_en_tabla(const texto_t clave, int valor, tabla &t);

/*
  Inserta en `t' las asociaciones definidas en la lista `asociaciones'.
 */
void insertar_lista_en_tabla(const lista asociaciones, tabla &t);

/*
 Libera la memoria asignada a `t' y todos sus elementos.
 */
void liberar_tabla(tabla &t);

/*
  Devuelve `true' si en `t' está definida la asociación para `clave',
  en cuyo caso además devuelve en `n' el valor asociado, o devuelve `false' y
  `n' es ignorado.
  El tiempo de ejecución es O(1) en promedio.
 */
bool valor_en_tabla(texto_t clave, const tabla t, int &n);
