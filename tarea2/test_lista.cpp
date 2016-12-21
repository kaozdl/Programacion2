#include "include/utils.h"
#include "include/texto.h"
#include "include/info.h"
#include "include/lista.h"
#include "include/uso_lista.h"

#include <stdio.h>

/*
  Test de lista.cpp.
  En Makefile se agregan reglas:
  make test_lista
  para compilar

  make correr_test_lista
  para correr (antes compila si es necesario)

  Se sugiere proceder por etapas descomentando un bloque en cada una,
  entender el código y determinar cual debe ser la salida y compararla con
  la obtenida y si es necesario hacer correcciones en lista.cpp, info.cpp y
  texto.cpp hasta obtener la salida correcta. Se debe controlar que las
  modificaciones no afecten los bloques que ya habían sido testeado antes.

  Cuando hay un error se imprime que es lo que lo genera. Lo correcto debe ser
  lo contrario.

 */

int main() {

  {
    printf("\n crear la estructura y liberar memoria.\n");
    lista lst = crear_lista();
    if (!es_vacia_lista(lst))
      perror("ERROR: lista no vacía. \n");

    liberar_lista(lst);
  }

  /*
  {
    printf("\n lista con un elemento.\n");

    lista lst = crear_lista();
    info_t info = crear_info(5, cadena_a_texto("hola"));
    insertar_despues(info, final_lista(lst), lst);
    if (es_vacia_lista(lst))
      perror ("ERROR: lista vacía. \n");
    liberar_lista(lst);

    lst = crear_lista();
    info = crear_info(5, cadena_a_texto("hola"));
    insertar_despues(info, inicio_lista(lst), lst);
    if (es_vacia_lista(lst))
      perror ("ERROR: lista vacía. \n");
    liberar_lista(lst);

    lst = crear_lista();
    info = crear_info(5, cadena_a_texto("hola"));
    insertar_antes(info, inicio_lista(lst), lst);
    if (es_vacia_lista(lst))
      perror ("ERROR: lista vacía. \n");
    liberar_lista(lst);

    lst = crear_lista();
    info = crear_info(5, cadena_a_texto("hola"));
    insertar_antes(info, final_lista(lst), lst);
    if (es_vacia_lista(lst))
      perror ("ERROR: lista vacía. \n");
    liberar_lista(lst);
  }

  {
    printf("\n inserción al final, al inicio y en el medio.\n");
    lista lst = crear_lista();
    info_t info = crear_info(2, cadena_a_texto("hola"));
    insertar_despues(info, final_lista(lst), lst);
    info = crear_info(4, cadena_a_texto("mundo!"));
    insertar_despues(info, final_lista(lst), lst);
    info = crear_info(3, cadena_a_texto(" "));
    insertar_antes(info, final_lista(lst), lst);
    info = crear_info(1, cadena_a_texto("¡"));
    insertar_antes(info, inicio_lista(lst), lst);

    if (es_vacia_lista(lst))
      perror ("ERROR: lista vacía. \n");
    imprimir_lista(lst);

    liberar_lista(lst);
  }

  {
    printf("\n validez, pertenencia y precedencia de localizadores.\n");
    lista lst1 = crear_lista();
    info_t info1 = crear_info(5, cadena_a_texto("hola"));
    insertar_antes(info1, final_lista(lst1), lst1);
    lista lst2 = crear_lista();
    info_t info2 = crear_info(1, cadena_a_texto("otro"));
    insertar_despues(info2, inicio_lista(lst2), lst2);

    localizador loc1 = inicio_lista(lst1);
    if (! es_localizador_lista(loc1))
      perror ("ERROR: localizador no es válido");
    if (! localizador_pertenece_a_lista(loc1,lst1))
      perror ("ERROR: localizador no pertenece a lst1");
    if (localizador_pertenece_a_lista(loc1,lst2))
      perror ("ERROR: localizador pertenece a lst2");
    loc1 = anterior(loc1,lst1);
    if (es_localizador_lista(loc1))
      perror ("ERROR: localizador es válido");

    info1 = crear_info(2, cadena_a_texto(" "));
    insertar_despues(info1, final_lista(lst1), lst1);
    info1 = crear_info(3, cadena_a_texto("mundo"));
    insertar_despues(info1, final_lista(lst1), lst1);

    loc1 = inicio_lista(lst1);
    if (! precede_en_lista(loc1, loc1, lst1))
      perror ("ERROR: no precede aunque son iguales");
    localizador loc2 = final_lista(lst1);
    if (! precede_en_lista(loc1, loc2, lst1))
      perror ("ERROR: no precede");
    if (precede_en_lista(loc2, loc1, lst1))
      perror ("ERROR: precede");

    liberar_lista(lst1);
    liberar_lista(lst2);
  }

  {
    printf("\n es_inicio y es_final.\n");
    lista lst = crear_lista();
    info_t info = crear_info(2, cadena_a_texto("hola"));
    insertar_despues(info, final_lista(lst), lst);
    info = crear_info(4, cadena_a_texto("mundo!"));
    insertar_despues(info, final_lista(lst), lst);
    info = crear_info(3, cadena_a_texto(" "));
    insertar_antes(info, final_lista(lst), lst);
    info = crear_info(1, cadena_a_texto("¡"));
    insertar_antes(info, inicio_lista(lst), lst);

    localizador loc = inicio_lista(lst);
    if (! es_inicio_lista(loc, lst))
      perror("ERROR: no es inicio");
    if (es_final_lista(loc, lst))
      perror("ERROR: es final");
    loc = siguiente(loc, lst);
    if (es_inicio_lista(loc, lst))
      perror("ERROR: es inicio");
    if (es_final_lista(loc, lst))
      perror("ERROR: es final");
    loc = final_lista(lst);
    if (! es_final_lista(loc, lst))
      perror("ERROR: no es final");
    if (es_inicio_lista(loc, lst))
      perror("ERROR: es inicio");

    liberar_lista(lst);
  }

  {
    printf("\n remueve penúltimo, primero, último y único.\n");
    lista lst = crear_lista();
    info_t info = crear_info(2, cadena_a_texto("hola"));
    insertar_despues(info, final_lista(lst), lst);
    info = crear_info(4, cadena_a_texto("mundo!"));
    insertar_despues(info, final_lista(lst), lst);
    info = crear_info(3, cadena_a_texto(" "));
    insertar_antes(info, final_lista(lst), lst);
    info = crear_info(1, cadena_a_texto("¡"));
    insertar_antes(info, inicio_lista(lst), lst);

    localizador loc = anterior(final_lista(lst), lst);
    remover_de_lista(loc, lst);
    imprimir_lista(lst);
    loc = inicio_lista(lst);
    remover_de_lista(loc, lst);
    imprimir_lista(lst);
    loc = final_lista(lst);
    remover_de_lista(loc, lst);
    imprimir_lista(lst);
    if (es_vacia_lista(lst))
      perror ("ERROR: lista vacía. \n");
    loc = final_lista(lst);
    remover_de_lista(loc, lst);
    imprimir_lista(lst);
    if (! es_vacia_lista(lst))
      perror ("ERROR: lista vacía. \n");

    liberar_lista(lst);
  }

  {
    printf("\n segmentos: igual, solo el primero y solo el último.\n");
    lista lst = crear_lista();
    info_t info = crear_info(2, cadena_a_texto("hola"));
    insertar_despues(info, final_lista(lst), lst);
    info = crear_info(4, cadena_a_texto("mundo!"));
    insertar_despues(info, final_lista(lst), lst);
    info = crear_info(3, cadena_a_texto(" "));
    insertar_antes(info, final_lista(lst), lst);
    info = crear_info(1, cadena_a_texto("¡"));
    insertar_antes(info, inicio_lista(lst), lst);

    lista sgm = segmento_lista (inicio_lista(lst), final_lista(lst), lst);
    imprimir_lista(sgm);
    liberar_lista(sgm);
    sgm = segmento_lista (inicio_lista(lst), inicio_lista(lst), lst);
    imprimir_lista(sgm);
    liberar_lista(sgm);
    sgm = segmento_lista (final_lista(lst), final_lista(lst), lst);
    imprimir_lista(sgm);
    liberar_lista(sgm);
    imprimir_lista(lst);

    liberar_lista(lst);
  }

  {
    printf("\n insertar segmento al final, en el medio y en lista vacía.\n");
    lista lst = crear_lista();
    info_t info = crear_info(2, cadena_a_texto("hola"));
    insertar_despues(info, final_lista(lst), lst);
    info = crear_info(4, cadena_a_texto("mundo!"));
    insertar_despues(info, final_lista(lst), lst);
    info = crear_info(3, cadena_a_texto(" "));
    insertar_antes(info, final_lista(lst), lst);
    info = crear_info(1, cadena_a_texto("¡"));
    insertar_antes(info, inicio_lista(lst), lst);

    lista sgm = segmento_lista (siguiente(inicio_lista(lst),lst),
  anterior(final_lista(lst),lst), lst);
    imprimir_lista(sgm);
    insertar_segmento_despues(sgm, final_lista(lst), lst);
    imprimir_lista(lst);
    imprimir_lista(sgm); // debe ser vacia
    insertar_segmento_despues(sgm, inicio_lista(lst), lst);
    imprimir_lista(lst);
    liberar_lista(sgm);
    sgm = segmento_lista (siguiente(inicio_lista(lst),lst),
  anterior(final_lista(lst),lst), lst);
    imprimir_lista(sgm);
    insertar_segmento_despues(sgm, inicio_lista(lst), lst);
    liberar_lista(sgm);
    imprimir_lista(lst);
    sgm = segmento_lista (siguiente(inicio_lista(lst),lst),
  anterior(final_lista(lst),lst), lst);
    liberar_lista(lst);
    lst = crear_lista();
    insertar_segmento_despues(sgm, inicio_lista(lst), lst);
    liberar_lista(sgm);
    imprimir_lista(lst);

    liberar_lista(lst);
  }

  {
    printf("\n separar segmento: primero, último y toda la lista.\n");
    lista lst = crear_lista();
    info_t info = crear_info(2, cadena_a_texto("hola"));
    insertar_despues(info, final_lista(lst), lst);
    info = crear_info(4, cadena_a_texto("mundo!"));
    insertar_despues(info, final_lista(lst), lst);
    info = crear_info(3, cadena_a_texto(" "));
    insertar_antes(info, final_lista(lst), lst);
    info = crear_info(1, cadena_a_texto("¡"));
    insertar_antes(info, inicio_lista(lst), lst);

    lista cut = separar_segmento (inicio_lista(lst), inicio_lista(lst), lst);
    imprimir_lista(cut);
    liberar_lista(cut);
    imprimir_lista(lst);
    cut = separar_segmento (final_lista(lst), final_lista(lst), lst);
    imprimir_lista(cut);
    liberar_lista(cut);
    imprimir_lista(lst);
    cut = separar_segmento (inicio_lista(lst), final_lista(lst), lst);
    imprimir_lista(cut);
    liberar_lista(cut);
    imprimir_lista(lst);

    liberar_lista(lst);
  }

  {
    printf("\n siguiente y anterior clave.\n");
    lista lst = crear_lista();
    info_t info = crear_info(2, cadena_a_texto("hola"));
    insertar_despues(info, final_lista(lst), lst);
    info = crear_info(4, cadena_a_texto("mundo!"));
    insertar_despues(info, final_lista(lst), lst);
    info = crear_info(3, cadena_a_texto(" "));
    insertar_antes(info, final_lista(lst), lst);
    info = crear_info(1, cadena_a_texto("¡"));
    insertar_antes(info, inicio_lista(lst), lst);

    localizador loc = siguiente_clave(1, inicio_lista(lst), lst);
    if (! es_localizador_lista(loc))
      perror("ERROR:1 está al inicio");
    loc = siguiente_clave(4, final_lista(lst), lst);
    if (! es_localizador_lista(loc))
      perror("ERROR:4 está al final");
    loc = siguiente_clave(3, inicio_lista(lst), lst);
    if (! es_localizador_lista(loc))
      perror("ERROR:3 está después del inicio");
    loc = siguiente_clave(1, siguiente(inicio_lista(lst),lst), lst);
    if (es_localizador_lista(loc))
      perror("ERROR:1 solo está al inicio");

    loc = anterior_clave(1, inicio_lista(lst), lst);
    if (! es_localizador_lista(loc))
      perror("ERROR:1 está al inicio");
    loc = anterior_clave(4, final_lista(lst), lst);
    if (! es_localizador_lista(loc))
      perror("ERROR:4 está al final");
    loc = anterior_clave(3, final_lista(lst), lst);
    if (! es_localizador_lista(loc))
      perror("ERROR:3 está antes del final");
    loc = anterior_clave(4, anterior(final_lista(lst),lst), lst);
    if (es_localizador_lista(loc))
      perror("ERROR:4 solo está al final");

    liberar_lista(lst);
  }

  {
    printf("\n intercambiar, cambiar, mover antes, info .\n");
    lista lst = crear_lista();
    info_t info = crear_info(2, cadena_a_texto("hola"));
    insertar_despues(info, final_lista(lst), lst);
    info = crear_info(4, cadena_a_texto("mundo!"));
    insertar_despues(info, final_lista(lst), lst);
    info = crear_info(3, cadena_a_texto(" "));
    insertar_antes(info, final_lista(lst), lst);
    info = crear_info(1, cadena_a_texto("¡"));
    insertar_antes(info, inicio_lista(lst), lst);

    localizador loc1 = inicio_lista(lst), loc2 = final_lista(lst);

    // intercambiar
    intercambiar(loc1, loc2, lst);
    imprimir_lista(lst);
    info_t info_en_loc = info_lista(loc1, lst);
    texto_t txt = info_a_texto(info_en_loc);
    escribir_texto(txt);
    escribir_nueva_linea();
    liberar_texto(txt);
    info_en_loc = info_lista(loc2, lst);
    txt = info_a_texto(info_en_loc);
    escribir_texto(txt);
    escribir_nueva_linea();
    liberar_texto(txt);

    // cambiar
    info = crear_info(2, cadena_a_texto("¡"));
    info_en_loc = info_lista(inicio_lista(lst), lst);
    cambiar_en_lista(info, inicio_lista(lst), lst);
    imprimir_lista(lst);
    txt = info_a_texto(info_en_loc);
    escribir_texto(txt);
    escribir_nueva_linea();
    liberar_texto(txt);
    liberar_info(info_en_loc);

    // mover_antes
    loc1 = siguiente(inicio_lista(lst), lst);
    loc2 = final_lista(lst);
    mover_antes(loc1, loc2, lst);
    imprimir_lista(lst);

    loc1 = inicio_lista(lst);
    loc2 = final_lista(lst);
    mover_antes(loc1, loc2, lst);
    imprimir_lista(lst);

    loc1 = inicio_lista(lst);
    loc2 = final_lista(lst);
    mover_antes(loc2, loc1, lst);
    imprimir_lista(lst);

    liberar_lista(lst);
  }
  */
  return 0;
}
