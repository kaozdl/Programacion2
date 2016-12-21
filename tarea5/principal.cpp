
/*
  Módulo principal de la tarea 5.

Intérprete de comandos para probar los módulos.

Están definidos una lista `lst', un binario `b', un conjunto `c', una
cola_de_prioridad `cp' con tamaño MAX_CP y un sistema s.


Cada comando tiene un nombre y una lista (posiblemente vacía) de parámetros.
Se asume que los comandos están bien formados. Esto implica que:
- el nombre es uno de los descritos más abajo;
- la cantidad y tipo de los parámetros cumplen con lo requerido;
- se cumplen las precondiciones de las operaciones invocadas.

Si un parámetro debe ser de tipo info_t su formato cumple con lo descrito en
`info_a_texto` del módulo `info`, con el agregado de que no puede incluir el
 símbolo ')'.
Una secuencia de elementos de un tipo es terminada por un espacio en blanco
seguido de un punto.

Descripción de los comandos:

Fin
   Termina el programa
# comentario
   Imprime nueva línea.
ingresar_localidades secuencia_info_t .
   Agrega a `s` cada elemento de la secuencia. El dato de texto es el nombre de
   la localidad y el dato numérico es la urgencia.
iniciar_pedidos max_prioridades
   Inicia los pedidos para `s` con max_prioridades posibles prioridades.
ingresar_pedidos secuencia_[id_loc info prioridad] .
   Ingresa los pedidos a `s`.
imprimir_totales
   Invoca a la función imprimir_totales de sistema.
procesar_rango id_rango
   Procesa el rango identificado con el valor id_rango entre 1 y 5.
reiniciar_sistema
   Se reinicia todos los valores del sistema.

linealizacion
   Imprime en orden los elementos de `f`.
balanceado secuencia_info_t .
   Construye `f` balanceado con los elementos de la secuencia, que deben estar
   ordenados de manera creciente según el dato de texto.
construir_cnj secuencia_info_t .
   construye `c` con la secuencia leída que debe estar ordenada de manera
   creciente según el dato de texto.
excluir secuencia_strings .
   excluye de `c` los elementos de la secuencia dada.
ops_cnj secuencia_info_t .
   opera en `c` con los elementos de la secuencia dada.
cola_prioridad secuencia_info_t .
   inserta en `cp` los elementos de la secuencia dada y opera con `cp`.
insertar_lista secuencia_info_t .
   Inserta en `lst` cada elemento de la secuencia leída.
recorrido
   recorre `lst` imprimiendo sus elementos.
segmentos clave1 clave2
   manipula la sublista de `lst` desde la primera aparición de `clave1` hasta
   la última aparición de `clave2`, donde `clave1` y `clave2` son enteros.
modificar_lista clave1 clave2
   modifica `lst`, utilizando las apariciones de los enteros `clave1` y
   `clave2`.
ero `clave` y `criterio`.
insertar_binario secuencia_info_t .
   Inserta en `b` cada elemento de la secuencia leída.
remover_binario secuencia_texto_t .
   Remueve de `b` cada elemento de la secuencia leída.
filtrar_binario clave criterio
   Invoca filtrar_binario en `b` con los parámetros leídos.
buscar_subarbol patron
   Invoca buscar_subarbol  en `b` con el patrón leído.
kesimo_subarbol cantidad
   Invoca kesimo_subarbol en `b` con la cantidad leída.



  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
*/

#include "include/utils.h"
#include "include/texto.h"
#include "include/info.h"
#include "include/lista.h"
#include "include/binario.h"
#include "include/conjunto.h"
#include "include/cola_de_prioridad.h"
#include "include/localidades.h"
#include "include/pedidos.h"
#include "include/sistema.h"

#include <assert.h>
#include <stdio.h>

#define MAX_RESTO_LINEA 200
#define MAX_LARGO_PALABRA 30
#define MAX_PILA 20
#define MAX_CP 15

// mensajes
const texto_t msg_fin = cadena_a_texto("Fin.");
const texto_t msg_cmd_no_reconocido = cadena_a_texto("Comando no reconocido.");

const texto_t prompt = char_a_texto('>');

const texto_t fin_comando = cadena_a_texto(".");

/* Estructura para identificar el nombre de comando */
enum enum_cmd_t {
  cmd_fin,
  cmd_comentario,
  cmd_ingresar_localidades,
  cmd_iniciar_pedidos,
  cmd_ingresar_pedidos,
  cmd_imprimir_totales,
  cmd_procesar_rango,
  cmd_reiniciar_sistema,
  cmd_linealizacion,
  cmd_balanceado,
  cmd_construir_cnj,
  cmd_excluir,
  cmd_ops_cnj,
  cmd_cola_prioridad,
  cmd_ins_lista,
  cmd_recorrido_lista,
  cmd_segmentos_lista,
  cmd_ins_binario,
  cmd_rmv_binario,
  cmd_flt_binario,
  cmd_bsc_subarbol,
  cmd_k_subarbol,
  cmd_finitario,
  cmd_liberar_estructuras,
  cmd_tiempo,
  no_reconocido
};
const nat cant_com = no_reconocido;

struct enum_nombre_cmd {
  const enum_cmd_t enum_cmd;
  const char *nombre_cmd;
};

/*
  Asociación entre nombre de comando y enumerado.
 */
const enum_nombre_cmd cmds[] = {
    {cmd_fin, "Fin"},
    {cmd_comentario, "#"},
    {cmd_ingresar_localidades, "ingresar_localidades"},
    {cmd_iniciar_pedidos, "iniciar_pedidos"},
    {cmd_ingresar_pedidos, "ingresar_pedidos"},
    {cmd_imprimir_totales, "imprimir_totales"},
    {cmd_procesar_rango, "procesar_rango"},
    {cmd_reiniciar_sistema, "reiniciar_sistema"},
    {cmd_linealizacion, "linealizacion"},
    {cmd_balanceado, "balanceado"},
    {cmd_construir_cnj, "construir_cnj"},
    {cmd_excluir, "excluir"},
    {cmd_ops_cnj, "ops_cnj"},
    {cmd_cola_prioridad, "cola_prioridad"},
    {cmd_ins_lista, "insertar_lista"},
    {cmd_recorrido_lista, "recorrido"},
    {cmd_segmentos_lista, "segmentos"},
    {cmd_ins_binario, "insertar_binario"},
    {cmd_rmv_binario, "remover_binario"},
    {cmd_flt_binario, "filtrar_binario"},
    {cmd_bsc_subarbol, "buscar_subarbol"},
    {cmd_k_subarbol, "kesimo_subarbol"},
    {cmd_liberar_estructuras, "liberar_estructuras"},
    {cmd_tiempo, "tiempo"}};

/*
  Devuelve el identificador de comando leido desde la entrada estándar.
 */
enum_cmd_t identificador_comando() {
  enum_cmd_t res = no_reconocido;
  texto_t nom_com = leer_palabra(MAX_LARGO_PALABRA);

  bool encontrado = false;
  nat i = cmd_fin; // = 0
  while ((!encontrado) && (i < cant_com)) {
    texto_t nom_item = cadena_a_texto(cmds[i].nombre_cmd);
    if (igual == comparar_texto(nom_com, nom_item)) {
      res = cmds[i].enum_cmd;
      encontrado = true;
    } else {
      i++;
    }
    liberar_texto(nom_item);
  }
  liberar_texto(nom_com);
  return res;
} // identificador_comando

/*
  Incrementa el contador de comandos y muestra el prompt.
 */
void mostrar_prompt(nat &cont_comandos) {
  cont_comandos++;
  texto_t cont_com_txt = int_a_texto(cont_comandos);
  escribir_texto(cont_com_txt);
  escribir_texto(prompt);
  liberar_texto(cont_com_txt);
} // mostrar_prompt

/*
 Imprime `txt` seguido de nueva línea.
 */
void imprimir_con_nl(texto_t txt) {
  escribir_texto(txt);
  escribir_nueva_linea();
} // imprimir_nl

/*
  Lee desde la entrada estándar un texto y devuelve su conversión a entero.
 */
int leer_int() {
  texto_t txt_int = leer_palabra(MAX_LARGO_PALABRA);
  int res = texto_a_int(txt_int);
  liberar_texto(txt_int);
  return res;
} // leer_int

/*
  Imprime `n` seguido de nueva línea.
 */
void imprimir_int(int n) {
  texto_t txt_int = int_a_texto(n);
  imprimir_con_nl(txt_int);
  liberar_texto(txt_int);
} // imprimir_int

/*
  Lee una lista de info_t desde la entrada estándar. Después de cada elemento
  hay un espacio en blanco. Termina con un punto.
 */
lista leer_lista() {
  lista res = crear_lista();
  info_t info = leer_info(MAX_LARGO_PALABRA);
  while (es_valida_info(info)) {
    insertar_despues(info, final_lista(res), res);
    info = leer_info(MAX_LARGO_PALABRA);
  }
  liberar_info(info);
  return res;
} // leer_lista

void tiempo_crear_balanceado() {
  lista lst = crear_lista();
  for (int i = 1000000; i < 6000000; i++) {
    insertar_despues(crear_info(i, int_a_texto(i)), final_lista(lst), lst);
  }
  binario bal = crear_balanceado(lst);
  liberar_binario(bal);
  liberar_lista(lst);
}

void tiempo_cnj() {
  lista lst = crear_lista();
  for (int i = 1000000; i <= 1700000; i++) {
    insertar_despues(crear_info(i, int_a_texto(i)), final_lista(lst), lst);
  }
  conjunto c1 = construir_conjunto(lst);
  liberar_lista(lst);

  lst = crear_lista();
  for (int i = 1400000; i <= 1900000; i++) {
    insertar_despues(crear_info(i, int_a_texto(i)), final_lista(lst), lst);
  }
  conjunto c2 = construir_conjunto(lst);
  liberar_lista(lst);

  printf("  diferencia. \n");
  conjunto d = diferencia(c1, c2);

  texto_t t1 = cadena_a_texto("1000000");
  texto_t t2 = cadena_a_texto("1400000");
  texto_t t3 = cadena_a_texto("1900000");
  assert(pertenece(t1, d) && !pertenece(t2, d) && !pertenece(t2, d) &&
         !pertenece(t3, d));

  printf("  pertenece. \n");
  for (int i = 0; i < 10000; i++) {
    pertenece(t1, d);
    pertenece(t2, d);
  }

  liberar_texto(t1);
  liberar_texto(t2);
  liberar_texto(t3);
  liberar_conjunto(c1);
  liberar_conjunto(c2);
  liberar_conjunto(d);
}

void tiempo_cp() {
  cola_de_prioridad cp = crear_cp(10000000);
  printf("  insertar. \n");
  for (int i = 10000000; i <= 1; i--) {
    info_t info = crear_info(i, int_a_texto(i));
    //    ins_unica_en_cp(info, numero_info(info), cp);
    insertar_en_cp(info, numero_info(info), cp);
  }
  printf("  eliminar. \n");
  for (int i = 10000000; i <= 1; i--)
    eliminar_prioritario(cp);

  liberar_cp(cp);
}

int main() {
  lista lst = crear_lista();
  binario b = crear_binario();
  conjunto c = crear_conjunto();
  cola_de_prioridad cp = crear_cp(MAX_CP);
  sistema s = iniciar_sistema();

  nat cont_comandos = 0;
  bool salir = false;
  while (!salir) {

    mostrar_prompt(cont_comandos);
    enum_cmd_t enum_com = identificador_comando();

    // procesar el comando
    switch (enum_com) {
    case cmd_fin:
      salir = true;
      imprimir_con_nl(msg_fin);
      break;
    case cmd_comentario:
      break;
    case cmd_ingresar_localidades: {
      info_t info = leer_info(MAX_LARGO_PALABRA);
      while (es_valida_info(info)) {
        assert((1 <= numero_info(info)) && (100 >= numero_info(info)));
        ingresar_localidad(copiar_texto(texto_info(info)), numero_info(info),
                           s);
        liberar_info(info);
        info = leer_info(MAX_LARGO_PALABRA);
      }
      liberar_info(info);
      break;
    }
    case cmd_iniciar_pedidos: {
      int max_prioridades = leer_int();
      assert(1 <= max_prioridades);
      printf("\n IDENTIFICADORES DE LOCALIDADES \n");
      iniciar_pedidos(max_prioridades, s);
      break;
    }
    case cmd_ingresar_pedidos: {
      texto_t palabra = leer_palabra(MAX_LARGO_PALABRA);
      while (comparar_texto(fin_comando, palabra) != igual) {
        info_t detalle = leer_info(MAX_LARGO_PALABRA);
        assert(numero_info(detalle) > 0);
        int prioridad = leer_int();
        assert(1 <= prioridad);
        ingresar_pedido(palabra, detalle, prioridad, s);
        liberar_texto(palabra);
        palabra = leer_palabra(MAX_LARGO_PALABRA);
      }
      liberar_texto(palabra);
      break;
    }
    case cmd_imprimir_totales: {
      printf("INFORME POR RANGOS\n");
      imprimir_totales(s);
      break;
    }
    case cmd_procesar_rango: {
      rango_t rango = leer_int();
      assert((1 <= rango) && (5 >= rango));
      procesar_rango(rango, s);
      break;
    }
    case cmd_reiniciar_sistema: {
      printf("\n  REINICIO DE SISTEMA \n");
      terminar_sistema(s);
      s = iniciar_sistema();
      break;
    }

    case cmd_linealizacion: {
      lista ord = linealizacion(b);
      imprimir_lista(ord);
      liberar_lista(ord);
      break;
    }
    case cmd_balanceado: {
      liberar_binario(b);
      lista ord = leer_lista();
      b = crear_balanceado(ord);
      escribir_nueva_linea();
      imprimir_binario(b);
      liberar_lista(ord);
      break;
    }
    case cmd_construir_cnj: {
      liberar_conjunto(c);
      lista ord = leer_lista();
      c = construir_conjunto(ord);
      liberar_lista(ord);
      break;
    }
    case cmd_excluir: {
      texto_t palabra = leer_palabra(MAX_LARGO_PALABRA);
      while (comparar_texto(fin_comando, palabra) != igual) {
        excluir(palabra, c);
        liberar_texto(palabra);
        palabra = leer_palabra(MAX_LARGO_PALABRA);
      }
      liberar_texto(palabra);
      if (es_vacio_conjunto(c)) {
        texto_t txt_vacio = cadena_a_texto("Vacio.");
        imprimir_con_nl(txt_vacio);
        liberar_texto(txt_vacio);
      }
      break;
    }
    case cmd_ops_cnj: {
      lista otra = leer_lista();
      localizador loc = inicio_lista(otra);
      conjunto cnj = crear_conjunto();
      while (es_localizador_lista(loc)) {
        info_t copia = copiar_info(info_lista(loc, otra));
        bool incluyo = incluir(copia, cnj);
        if (!incluyo)
          liberar_info(copia);
        loc = siguiente(loc, otra);
      }
      loc = inicio_lista(otra);

      conjunto dif = diferencia(cnj, c);
      conjunto inter = interseccion(cnj, c);

      nat cant_dif = 0, cant_inter = 0;
      while (es_localizador_lista(loc)) {
        texto_t texto = texto_info(info_lista(loc, otra));
        if (pertenece(texto, dif))
          cant_dif++;
        if (pertenece(texto, inter))
          cant_inter++;

        loc = siguiente(loc, otra);
      }
      imprimir_int(cant_dif);
      imprimir_int(cant_inter);

      liberar_lista(otra);
      liberar_conjunto(cnj);
      liberar_conjunto(dif);
      liberar_conjunto(inter);
      break;
    }
    case cmd_cola_prioridad: {
      prio_t valor_p = leer_int();
      assert((1 <= valor_p) && (valor_p <= MAX_CP));
      lista lst = lista_en_cp(valor_p, cp);
      imprimir_lista(lst);
      if (es_vacia_lista(lst))
        liberar_lista(lst);

      info_t info = leer_info(MAX_LARGO_PALABRA);
      while (es_valida_info(info)) {
        assert((1 <= numero_info(info)) && (numero_info(info) <= MAX_CP));
        insertar_en_cp(info, numero_info(info), cp);
        info = leer_info(MAX_LARGO_PALABRA);
      }
      liberar_info(info);

      if (!es_vacia_cp(cp)) {
        info = prioritario(cp);
        texto_t txt = info_a_texto(info);
        imprimir_con_nl(txt);
        liberar_texto(txt);
      }
      eliminar_prioritario(cp);

      break;
    }

    case cmd_ins_lista: {
      info_t info = leer_info(MAX_LARGO_PALABRA);
      while (es_valida_info(info)) {
        insertar_despues(info, final_lista(lst), lst);
        info = leer_info(MAX_LARGO_PALABRA);
      }
      liberar_info(info);
      texto_t txt = cadena_a_texto("primero");
      info = crear_info(0, txt);
      insertar_antes(info, inicio_lista(lst), lst);
      imprimir_lista(lst);
      break;
    }
    case cmd_recorrido_lista: {
      if (!es_vacia_lista(lst)) {
        localizador loc = inicio_lista(lst);
        while (es_localizador_lista(loc)) {
          texto_t txt = info_a_texto(info_lista(loc, lst));
          escribir_texto(txt);
          liberar_texto(txt);
          loc = siguiente(loc, lst);
        }
        loc = final_lista(lst);
        while (es_localizador_lista(loc)) {
          texto_t txt = info_a_texto(info_lista(loc, lst));
          escribir_texto(txt);
          liberar_texto(txt);
          loc = anterior(loc, lst);
        }
        escribir_nueva_linea();
      }
      break;
    }
    case cmd_segmentos_lista: {
      int clave1 = leer_int();
      int clave2 = leer_int();
      localizador desde = siguiente_clave(clave1, inicio_lista(lst), lst);
      localizador hasta = anterior_clave(clave2, final_lista(lst), lst);
      if (es_localizador_lista(desde) && es_localizador_lista(hasta) &&
          precede_en_lista(desde, hasta, lst)) {
        lista sgm = separar_segmento(desde, hasta, lst);
        lista copia = segmento_lista(inicio_lista(sgm), final_lista(sgm), sgm);
        imprimir_lista(sgm);
        liberar_lista(sgm);
        insertar_segmento_despues(copia, final_lista(lst), lst);
        liberar_lista(copia);
        imprimir_lista(lst);
      }
      break;
    }

    case cmd_ins_binario: {
      info_t info = leer_info(MAX_LARGO_PALABRA);
      while (es_valida_info(info)) {
        bool inserto = insertar_en_binario(info, b);
        if (!inserto)
          liberar_info(info);
        info = leer_info(MAX_LARGO_PALABRA);
      }
      liberar_info(info);
      escribir_nueva_linea();
      imprimir_binario(b);
      if (!es_vacio_binario(b)) {
        imprimir_int(altura_binario(izquierdo(b)));
        imprimir_int(cantidad_binario(derecho(b)));
      }
      break;
    }
    case cmd_rmv_binario: {
      texto_t palabra = leer_palabra(MAX_LARGO_PALABRA);
      while (comparar_texto(fin_comando, palabra) != igual) {
        remover_de_binario(palabra, b);
        liberar_texto(palabra);
        palabra = leer_palabra(MAX_LARGO_PALABRA);
      }
      liberar_texto(palabra);
      escribir_nueva_linea();
      if (!es_vacio_binario(b)) {
        info_t mayor = remover_mayor(b);
        texto_t txt_mayor = info_a_texto(mayor);
        imprimir_con_nl(txt_mayor);
        liberar_texto(txt_mayor);
        liberar_info(mayor);
      }
      imprimir_binario(b);
      break;
    }
    case cmd_flt_binario: {
      int clave = leer_int();
      texto_t palabra = leer_palabra(MAX_LARGO_PALABRA);
      comp_t criterio = texto_a_comp(palabra);
      liberar_texto(palabra);
      binario flt = crear_filtrado(clave, criterio, b);
      escribir_nueva_linea();
      imprimir_binario(flt);
      liberar_binario(flt);
      break;
    }
    case cmd_k_subarbol: {
      int k = leer_int();
      binario sub = kesimo_subarbol(k, b);
      if (!es_vacio_binario(sub)) {
        texto_t palabra = info_a_texto(raiz_binario(sub));
        imprimir_con_nl(palabra);
        liberar_texto(palabra);
      }
      break;
    }

    case cmd_liberar_estructuras: {
      liberar_lista(lst);
      lst = crear_lista();
      liberar_binario(b);
      b = crear_binario();
      liberar_conjunto(c);
      c = crear_conjunto();
      liberar_cp(cp);
      cp = crear_cp(MAX_CP);
      terminar_sistema(s);
      s = iniciar_sistema();
      break;
    }

    case cmd_tiempo: {
      printf("Crear balanceado. \n");
      tiempo_crear_balanceado();
      printf("Set. \n");
      tiempo_cnj();
      printf("Cola de prioridad. \n");
      tiempo_cp();
      break;
    }

    default:
      imprimir_con_nl(msg_cmd_no_reconocido);
      break;
    } // switch
    texto_t resto_linea = leer_resto_linea(MAX_RESTO_LINEA);
    liberar_texto(resto_linea);
  } // while

  liberar_conjunto(c);
  liberar_cp(cp);
  liberar_lista(lst);
  liberar_binario(b);
  terminar_sistema(s);
  return 0;
}
