/*
  Módulo de implementación de 'texto'.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#include "../include/utils.h"
#include "../include/texto.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <assert.h>

/*
  Se define `array_char` como un alias de `char *`, y representa los arrays de
  caracteres cuya dimensión es determinada en tiempo de ejecución.
  Los arrays son de tipo puntero a algo porque su valor es la dirección de
  memoria del primer elemento del array.
 */
typedef char *array_char;

/*
  Aquí se define la representación de `rep_texto`.
  Por lo tanto, `texto_t` es un puntero a un array de caracteres.
 */
struct rep_texto {
  array_char caracteres;
};

unsigned long hash_texto(const texto_t t, nat mod) {
  unsigned long res = 0; // u otro número, 5381
  for (nat i = 0; i < strlen(t->caracteres); i++)
    res = (res << 5) + res + t->caracteres[i];
  // res = res * 33 + t->caracteres[i]
  // con 33 = 2^5 + 1, que es un número obtenido experimentalmente

  // res << 5 desplaza `res` 5 bits hacia la derecha lo cual es una forma
  // eficiente de calcular res * 2^5

  return res % mod;
}
