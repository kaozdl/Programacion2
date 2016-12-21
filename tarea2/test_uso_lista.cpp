#include "include/utils.h"
#include "include/texto.h"
#include "include/info.h"
#include "include/lista.h"
#include "include/uso_lista.h"

#include <stdio.h>

/*
  Test de uso_lista.cpp.
  En Makefile se agregan reglas:
  make test_uso_lista
  para compilar

  make correr_test_uso_lista
  para correr (antes compila si es necesario)

  Se sugiere proceder por etapas descomentando un bloque en cada una,
  entender el código y determinar cual debe ser la salida y compararla con
  la obtenida y si es necesario hacer correcciones en uso_lista.cpp y
  módulos anteriores hasta obtener la salida correcta. Se debe controlar que
  las modificaciones no afecten los bloques que ya habían sido testeado antes.

  Cuando hay un error se imprime que es lo que lo genera. Lo correcto debe ser
  lo contrario.

 */

/*
  Imprime el elemento de `lst` al que se accede desde `loc`.
  Precondición: `lst´ no es vacía.
 */
void imprimir_elemento(const localizador loc, const lista lst) {
  info_t info = info_lista(loc, lst);
  texto_t txt = info_a_texto(info);
  escribir_texto(txt);
  escribir_nueva_linea();
  liberar_texto(txt);
}

int main() {

  {
    printf("\n pertenece, longitud, cantidad .\n");
    lista lst = crear_lista();

    if (pertenece(9, lst))
      perror("ERROR: 9 pertenece. \n");
    printf("%d \n", longitud(lst));
    printf("%d \n", cantidad(1, lst));

    info_t info = crear_info(2, cadena_a_texto("hola"));
    insertar_despues(info, final_lista(lst), lst);
    info = crear_info(4, cadena_a_texto("mundo!"));
    insertar_despues(info, final_lista(lst), lst);
    info = crear_info(2, cadena_a_texto(" "));
    insertar_antes(info, final_lista(lst), lst);
    info = crear_info(1, cadena_a_texto("¡"));
    insertar_antes(info, inicio_lista(lst), lst);

    if (!pertenece(1, lst))
      perror("ERROR: 1 no pertenece. \n");
    if (!pertenece(4, lst))
      perror("ERROR: 4 no pertenece. \n");
    if (pertenece(9, lst))
      perror("ERROR: 9 pertenece. \n");

    printf("%d \n", longitud(lst));
    printf("%d \n", cantidad(1, lst));
    printf("%d \n", cantidad(2, lst));
    printf("%d \n", cantidad(9, lst));

    liberar_lista(lst);
  }
  /*
  {
    printf("\n son_numeros_iguales .\n");
    lista lst1 = crear_lista(), lst2 = crear_lista();
    if (!son_numeros_iguales(lst1, lst2))
      perror("ERROR: no son numeros iguales aunque son vacías. \n");

    info_t info = crear_info(2, cadena_a_texto("hola"));
    insertar_despues(info, final_lista(lst1), lst1);
    if (son_numeros_iguales(lst1, lst2))
      perror("ERROR: son numeros iguales aunque una es vacía. \n");
    info = crear_info(3, cadena_a_texto("hola"));
    insertar_despues(info, final_lista(lst2), lst2);
    if (son_numeros_iguales(lst1, lst2))
      perror("ERROR: son numeros iguales. \n");
    info = crear_info(2, cadena_a_texto("mundo"));
    insertar_antes(info, inicio_lista(lst2), lst2);
    if (son_numeros_iguales(lst1, lst2))
      perror("ERROR: son numeros iguales aunque una es más larga. \n");
    info = crear_info(3, cadena_a_texto("hola"));
    insertar_despues(info, final_lista(lst1), lst1);
    if (!son_numeros_iguales(lst1, lst2))
      perror("ERROR: no son numeros iguales. \n");
    info = crear_info(3, cadena_a_texto("hola"));
    insertar_despues(info, final_lista(lst1), lst1);
    if (son_numeros_iguales(lst1, lst2))
      perror("ERROR: son numeros iguales. \n");

    liberar_lista(lst1);
    liberar_lista(lst2);
  }

  {
    printf("\n esta ordenada.\n");
    lista lst = crear_lista();
    if (!esta_ordenada(lst))
      perror("ERROR: no está ordenada aunque es vacía. \n");

    info_t info = crear_info(2, cadena_a_texto("hola"));
    insertar_despues(info, final_lista(lst), lst);
    if (!esta_ordenada(lst))
      perror("ERROR: no está ordenada aunque tiene solo un elemento. \n");
    info = crear_info(2, cadena_a_texto("mundo"));
    insertar_despues(info, final_lista(lst), lst);
    if (!esta_ordenada(lst))
      perror(
          "ERROR: no está ordenada aunque tiene los elementos son iguales. \n");
    info = crear_info(3, cadena_a_texto("!"));
    insertar_despues(info, final_lista(lst), lst);
    if (!esta_ordenada(lst))
      perror("ERROR: no está ordenada. \n");
    info = crear_info(1, cadena_a_texto("!"));
    insertar_despues(info, final_lista(lst), lst);
    if (esta_ordenada(lst))
      perror("ERROR: está ordenada. \n");

    liberar_lista(lst);
  }

  {
    printf("\n concatenar .\n");
    lista lst1 = crear_lista(), lst2 = crear_lista();
    lista concat;
    concat = concatenar(lst1, lst2);
    imprimir_lista(concat);
    liberar_lista(concat);

    info_t info = crear_info(2, cadena_a_texto("hola"));
    insertar_despues(info, final_lista(lst1), lst1);
    info = crear_info(2, cadena_a_texto("mundo"));
    insertar_despues(info, final_lista(lst1), lst1);
    concat = concatenar(lst1, lst2);
    imprimir_lista(concat);
    liberar_lista(concat);
    concat = concatenar(lst2, lst1);
    imprimir_lista(concat);
    liberar_lista(concat);

    info = crear_info(2, cadena_a_texto(" "));
    insertar_despues(info, final_lista(lst2), lst2);
    info = crear_info(2, cadena_a_texto("!"));
    insertar_despues(info, final_lista(lst2), lst2);
    concat = concatenar(lst1, lst2);
    imprimir_lista(concat);
    liberar_lista(concat);

    liberar_lista(lst1);
    liberar_lista(lst2);
  }

  {
    printf("\n reversa .\n");
    lista lst = crear_lista();
    lista rev = reversa(lst);
    imprimir_lista(rev);
    liberar_lista(rev);

    info_t info = crear_info(2, cadena_a_texto("hola"));
    insertar_despues(info, final_lista(lst), lst);
    rev = reversa(lst);
    imprimir_lista(rev);
    liberar_lista(rev);

    info = crear_info(2, cadena_a_texto(" "));
    insertar_despues(info, final_lista(lst), lst);
    info = crear_info(2, cadena_a_texto("mundo"));
    insertar_despues(info, final_lista(lst), lst);
    info = crear_info(2, cadena_a_texto("!"));
    insertar_despues(info, final_lista(lst), lst);
    rev = reversa(lst);
    imprimir_lista(rev);
    liberar_lista(rev);

    liberar_lista(lst);
  }

  {
    printf("\n primer mayor.\n");
    lista lst = crear_lista();

    info_t info = crear_info(1, cadena_a_texto("hola"));
    insertar_despues(info, final_lista(lst), lst);
    localizador loc = inicio_lista(lst);
    loc = primer_mayor(loc, lst);
    imprimir_elemento(loc, lst);

    info = crear_info(9, cadena_a_texto("!"));
    insertar_despues(info, final_lista(lst), lst);
    loc = final_lista(lst);
    loc = primer_mayor(loc, lst);
    imprimir_elemento(loc, lst);

    info = crear_info(9, cadena_a_texto("."));
    insertar_despues(info, final_lista(lst), lst);
    loc = final_lista(lst);
    loc = primer_mayor(loc, lst);
    imprimir_elemento(loc, lst);

    info = crear_info(6, cadena_a_texto("mundo"));
    insertar_despues(info, inicio_lista(lst), lst);
    info = crear_info(5, cadena_a_texto(" "));
    insertar_despues(info, final_lista(lst), lst);
    loc = final_lista(lst);
    loc = primer_mayor(loc, lst);
    imprimir_elemento(loc, lst);

    liberar_lista(lst);
  }

  {
    printf("\n retroceder.\n");
    lista lst = crear_lista();

    info_t info = crear_info(1, cadena_a_texto("hola"));
    insertar_despues(info, final_lista(lst), lst);
    localizador loc = final_lista(lst);
    retroceder(loc, lst);
    imprimir_lista(lst);
    info = crear_info(9, cadena_a_texto("!"));
    insertar_despues(info, final_lista(lst), lst);
    info = crear_info(9, cadena_a_texto("."));
    insertar_despues(info, final_lista(lst), lst);
    loc = final_lista(lst);
    retroceder(loc, lst);
    imprimir_lista(lst);
    info = crear_info(6, cadena_a_texto("mundo"));
    insertar_despues(info, inicio_lista(lst), lst);
    info = crear_info(5, cadena_a_texto(" "));
    insertar_despues(info, final_lista(lst), lst);
    imprimir_lista(lst);
    loc = final_lista(lst);
    retroceder(loc, lst);
    imprimir_lista(lst);

    liberar_lista(lst);
  }

  {
    printf("\n ordenar.\n");
    lista lst = crear_lista();
    ordenar(lst);
    imprimir_lista(lst);

    info_t info = crear_info(5, cadena_a_texto("hola"));
    insertar_despues(info, final_lista(lst), lst);
    ordenar(lst);
    imprimir_lista(lst);
    info = crear_info(8, cadena_a_texto("hola"));
    insertar_despues(info, final_lista(lst), lst);
    ordenar(lst);
    imprimir_lista(lst);
    info = crear_info(2, cadena_a_texto("hola"));
    insertar_despues(info, final_lista(lst), lst);
    info = crear_info(6, cadena_a_texto("hola"));
    insertar_antes(info, inicio_lista(lst), lst);
    imprimir_lista(lst);
    ordenar(lst);
    imprimir_lista(lst);

    liberar_lista(lst);
  }

  {
    printf("\n unificar.\n");
    lista lst = crear_lista();
    unificar(lst);
    imprimir_lista(lst);

    info_t info = crear_info(5, cadena_a_texto("hola"));
    insertar_despues(info, final_lista(lst), lst);
    unificar(lst);
    imprimir_lista(lst);
    info = crear_info(8, cadena_a_texto("hola"));
    insertar_despues(info, final_lista(lst), lst);
    unificar(lst);
    imprimir_lista(lst);
    info = crear_info(5, cadena_a_texto("hol"));
    insertar_antes(info, inicio_lista(lst), lst);
    info = crear_info(8, cadena_a_texto("hol"));
    insertar_despues(info, final_lista(lst), lst);
    info = crear_info(5, cadena_a_texto("ho"));
    insertar_antes(info, inicio_lista(lst), lst);
    info = crear_info(2, cadena_a_texto("hola"));
    insertar_antes(info, inicio_lista(lst), lst);
    info = crear_info(2, cadena_a_texto("h"));
    insertar_antes(info, inicio_lista(lst), lst);
    imprimir_lista(lst);
    unificar(lst);
    imprimir_lista(lst);

    liberar_lista(lst);
  }

  {
    printf("\n mezcla.\n");
    lista lst1 = crear_lista(), lst2 = crear_lista();
    lista mzc = mezcla(lst1, lst2);
    imprimir_lista(mzc);
    liberar_lista(mzc);

    info_t info = crear_info(2, cadena_a_texto("hola"));
    insertar_despues(info, final_lista(lst1), lst1);
    info = crear_info(2, cadena_a_texto("mundo"));
    insertar_despues(info, final_lista(lst1), lst1);
    mzc = mezcla(lst1, lst2);
    imprimir_lista(mzc);
    liberar_lista(mzc);
    mzc = mezcla(lst2, lst1);
    imprimir_lista(mzc);
    liberar_lista(mzc);

    info = crear_info(3, cadena_a_texto("!"));
    insertar_despues(info, final_lista(lst1), lst1);
    info = crear_info(1, cadena_a_texto("¡"));
    insertar_despues(info, final_lista(lst2), lst2);
    info = crear_info(1, cadena_a_texto("hola"));
    insertar_despues(info, final_lista(lst2), lst2);
    info = crear_info(2, cadena_a_texto(" "));
    insertar_despues(info, final_lista(lst2), lst2);
    info = crear_info(4, cadena_a_texto("!"));
    insertar_despues(info, final_lista(lst2), lst2);
    mzc = mezcla(lst1, lst2);
    imprimir_lista(mzc);
    liberar_lista(mzc);
    mzc = mezcla(lst2, lst1);
    imprimir_lista(mzc);
    liberar_lista(mzc);

    liberar_lista(lst1);
    liberar_lista(lst2);
  }

  {
    printf("\n cambiar todos.\n");
    lista lst = crear_lista();
    cambiar_todos(3, 5, lst);
    imprimir_lista(lst);
    info_t info = crear_info(2, cadena_a_texto("hola"));
    insertar_despues(info, final_lista(lst), lst);
    cambiar_todos(3, 5, lst);
    imprimir_lista(lst);
    info = crear_info(3, cadena_a_texto(" "));
    insertar_despues(info, final_lista(lst), lst);
    info = crear_info(2, cadena_a_texto("mundo"));
    insertar_despues(info, final_lista(lst), lst);
    info = crear_info(3, cadena_a_texto("!"));
    insertar_despues(info, final_lista(lst), lst);
    info = crear_info(3, cadena_a_texto("¡"));
    insertar_antes(info, inicio_lista(lst), lst);
    imprimir_lista(lst);
    cambiar_todos(3, 5, lst);
    imprimir_lista(lst);

    liberar_lista(lst);
  }

  {
    printf("\n filtrado.\n");
    lista lst = crear_lista();
    lista flt = filtrado(4, menor, lst);
    imprimir_lista(flt);
    liberar_lista(flt);

    info_t info = crear_info(2, cadena_a_texto("hola"));
    insertar_despues(info, final_lista(lst), lst);
    flt = filtrado(4, menor, lst);
    imprimir_lista(flt);
    liberar_lista(flt);

    info = crear_info(4, cadena_a_texto(" "));
    insertar_despues(info, final_lista(lst), lst);
    info = crear_info(3, cadena_a_texto("mundo"));
    insertar_despues(info, final_lista(lst), lst);
    info = crear_info(9, cadena_a_texto("!"));
    insertar_despues(info, final_lista(lst), lst);
    info = crear_info(-5, cadena_a_texto("¡"));
    insertar_antes(info, inicio_lista(lst), lst);
    flt = filtrado(4, menor, lst);
    imprimir_lista(flt);
    liberar_lista(flt);
    flt = filtrado(4, mayor, lst);
    imprimir_lista(flt);
    liberar_lista(flt);
    flt = filtrado(8, igual, lst);
    imprimir_lista(flt);
    liberar_lista(flt);

    liberar_lista(lst);
  }

  {
    printf("\n sublista.\n");
    lista lst = crear_lista();

    info_t info = crear_info(2, cadena_a_texto("hola"));
    insertar_despues(info, final_lista(lst), lst);
    lista sub = sublista(2, 2, lst);
    imprimir_lista(sub);
    liberar_lista(sub);
    info = crear_info(3, cadena_a_texto(" "));
    insertar_despues(info, final_lista(lst), lst);
    sub = sublista(2, 2, lst);
    imprimir_lista(sub);
    liberar_lista(sub);
    sub = sublista(3, 3, lst);
    imprimir_lista(sub);
    liberar_lista(sub);
    info = crear_info(4, cadena_a_texto("mundo"));
    insertar_despues(info, final_lista(lst), lst);
    info = crear_info(5, cadena_a_texto("!"));
    insertar_despues(info, final_lista(lst), lst);
    info = crear_info(6, cadena_a_texto("."));
    insertar_despues(info, final_lista(lst), lst);
    sub = sublista(2, 6, lst);
    imprimir_lista(sub);
    liberar_lista(sub);
    sub = sublista(3, 5, lst);
    imprimir_lista(sub);
    liberar_lista(sub);

    liberar_lista(lst);
  }
  */
  return 0;
}
