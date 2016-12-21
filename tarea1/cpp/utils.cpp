/* 4580203 */
#include "../include/utils.h"

#include <stdio.h>

void imprimir_comp(const comp_t comp) {
  switch (comp) {
  case menor: {
    printf("<");
    /* En general, debe usarse break para evitar que siga procesando los otros
       casos. */
    break;
  }
  case igual: {
    printf("=");
    break;
  }
  case mayor: {
    printf(">");
    break;
  }
  }
} // imprimir_comp
