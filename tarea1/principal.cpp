/*
  Módulo principal de la tarea 1.

  Prueba las operaciones declaradas en 'texto.h'.

  Lee desde la entrada estándar 'MAX_TXT' líneas o hasta encontrar una línea en
  blanco.
  (Se asume que cada línea tiene una longitud máxima de 'MAX_LARGO'.)

  Luego lee la próxima palabra, que será considerada como un natural.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
*/

#include "include/utils.h"
#include "include/texto.h"
#include <stdio.h>

#define MAX_TXT 10   // máxima cantidad de textos
#define MAX_LARGO 80 // máximo largo de los textos

/*
  Array de `cantidad` elementos de tipo `texto`.
*/
typedef texto_t *array_texto;
struct secuencia_textos {
  array_texto elementos;
  nat tamanio;
  nat cantidad;
};

int main() {
  secuencia_textos entrada;
  entrada.tamanio = MAX_TXT;
  entrada.elementos = new texto_t[entrada.tamanio];
  for (nat i = 0; i < entrada.tamanio; i++)
    entrada.elementos[i] = texto_vacio();

  nat cont_textos = 0;
  bool hay_nulo = false;

  // leer la entrada
  while ((!hay_nulo) && (cont_textos < MAX_TXT)) {
    texto_t linea = leer_resto_linea(MAX_LARGO);
    if (es_texto_vacio(linea)) {
      hay_nulo = true;
    } else {
      liberar_texto(entrada.elementos[cont_textos]); // a pesar de ser nulo
      entrada.elementos[cont_textos] = copiar_texto(linea);
      cont_textos++;
    }
    liberar_texto(linea);
  }

  entrada.cantidad = cont_textos;
  if (cont_textos == 0)
    fputs("La primera línea está en blanco. \n", stdout);
  else {
    // concatenar las líneas de entrada intercalando un separador
    texto_t sep = char_a_texto('|');
    texto_t union_entrada = copiar_texto(entrada.elementos[0]);
    for (nat i = 1; i < entrada.cantidad; i++) {
      texto_t copia = concatenar_texto(union_entrada, sep);
      liberar_texto(union_entrada);
      union_entrada = concatenar_texto(copia, entrada.elementos[i]);
      liberar_texto(copia);
    }
    escribir_texto(union_entrada);
    escribir_nueva_linea();
    liberar_texto(union_entrada);
    liberar_texto(sep);

    // tabla con longitudes y textos
    fputs("Longitud  Texto \n", stdout);
    for (nat i = 0; i < entrada.cantidad; i++) {
      printf("%8d  ", longitud_texto(entrada.elementos[i]));
      escribir_texto(entrada.elementos[i]);
      escribir_nueva_linea();
    }

    // comparar
    texto_t mitad = cadena_a_texto("mitad");
    for (nat i = 0; i < entrada.cantidad; i++) {
      comp_t res = comparar_texto(mitad, entrada.elementos[i]);
      escribir_texto(mitad);
      printf(" ");
      imprimir_comp(res);
      printf(" ");
      escribir_texto(entrada.elementos[i]);
      escribir_nueva_linea();
    }
    liberar_texto(mitad);
  }

  for (nat i = 0; i < entrada.cantidad; i++)
    liberar_texto(entrada.elementos[i]);
  delete[] entrada.elementos;

  /* String que será convertido en entero. */
  texto_t str_entero = leer_palabra(20);
  int conv = texto_a_int(str_entero);
  printf("La conversión es %d.\n", conv);
  liberar_texto(str_entero);
  str_entero = int_a_texto(conv);
  fputs("El inicio numérico de la palabra leida era ", stdout);
  escribir_texto(str_entero);
  liberar_texto(str_entero);
  fputs(".\n", stdout);
  return 0;
}
