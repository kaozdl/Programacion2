
/*
  Módulo principal de la tarea 4.

Intérprete de comandos para probar los módulos.

Están definidos una lista `lst`, un binario `b`,una pila `p`, una cola de
binarios `q`, un conjunto `c`, una cola_de_prioridad `cp` con tamaño MAX_CP.

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
linealizacion
   Imprime en orden los elementos de `f`.
balanceado secuencia_info_t .
   Construye `f` balanceado con los elementos de la secuencia, que deben estar
   ordenados de manera creciente según el dato de texto.
por_niveles
   Imprime `f` por niveles, uno por línea, desde las hojas hacia la raíz.
apilar secuencia_strings .
   apila en `p` los strings de la secuencia leída.
desapilar cantidad
   desapila `cantidad` elementos de la cima de `p`.
encolar
   encola en orden los subárboles de `b`.
desencolar cantidad
   desapila `cantidad` elementos del frente de `q`.
construir_cnj secuencia_info_t .
   construye `c` con la secuencia leída que debe estar ordenada de manera
   creciente según el dato de texto.
excluir secuencia_strings .
   excluye de `c` los elementos de la secuencia dada.
ops_cnj secuencia_info_t .
   opera en `c` con los elementos de la secuencia dada.
cola_prioridad secuencia_info_t .
   inserta en `cp` los elementos de la secuencia dada y opera con `cp`.
tiempo_balanceado
   Controla especificación de tiempo en crear_balanceado
tiempo_cnj
   Controla especificación de tiempo en conjunto
tiempo_cp
   Controla especificación de tiempo en cola_de_prioridad

Comandos de tareas anteriores
insertar_lista secuencia_info_t .
   Inserta en `lst` cada elemento de la secuencia leída.
recorrido
   recorre `lst` imprimiendo sus elementos.
segmentos clave1 clave2
   manipula la sublista de `lst` desde la primera aparición de `clave1` hasta
   la última aparición de `clave2`, donde `clave1` y `clave2` son enteros.
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
liberar_estructuras
   libera la memoria asignada a `lst`, `b` `p`, `q`, `c`  y `cp` los vuelve a
   crear.



  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
*/

#include "include/utils.h"
#include "include/texto.h"
#include "include/info.h"
#include "include/lista.h"
#include "include/binario.h"
#include "include/pila.h"
#include "include/cola_binarios.h"
#include "include/conjunto.h"
#include "include/cola_de_prioridad.h"

#include <assert.h>
#include <stdio.h>

#define MAX_RESTO_LINEA 200
#define MAX_LARGO_PALABRA 30
#define MAX_PILA 20
#define MAX_CP 100

// mensajes
const texto_t msg_fin = cadena_a_texto("Fin.");
const texto_t msg_cmd_no_reconocido = cadena_a_texto("Comando no reconocido.");

const texto_t prompt = char_a_texto('>');

const texto_t fin_comando = cadena_a_texto(".");

/* Estructura para identificar el nombre de comando */
enum enum_cmd_t {
  cmd_fin,
  cmd_comentario,
  cmd_linealizacion,
  cmd_balanceado,
  cmd_por_niveles,
  cmd_apilar,
  cmd_desapilar,
  cmd_encolar,
  cmd_desencolar,
  cmd_construir_cnj,
  cmd_excluir,
  cmd_ops_cnj,
  cmd_cola_prioridad,
  cmd_tiempo_balanceado,
  cmd_tiempo_cnj,
  cmd_tiempo_cp,

  cmd_ins_lista,
  cmd_recorrido_lista,
  cmd_segmentos_lista,
  cmd_ins_binario,
  cmd_rmv_binario,
  cmd_flt_binario,
  cmd_bsc_subarbol,
  cmd_k_subarbol,

  cmd_liberar_estructuras,
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
    {cmd_linealizacion, "linealizacion"},
    {cmd_balanceado, "balanceado"},
    {cmd_por_niveles, "por_niveles"},
    {cmd_apilar, "apilar"},
    {cmd_desapilar, "desapilar"},
    {cmd_encolar, "encolar"},
    {cmd_desencolar, "desencolar"},
    {cmd_construir_cnj, "construir_cnj"},
    {cmd_excluir, "excluir"},
    {cmd_ops_cnj, "ops_cnj"},
    {cmd_cola_prioridad, "cola_prioridad"},
    {cmd_tiempo_balanceado, "tiempo_balanceado"},
    {cmd_tiempo_cnj, "tiempo_cnj"},
    {cmd_tiempo_cp, "tiempo_cp"},

    {cmd_ins_lista, "insertar_lista"},
    {cmd_recorrido_lista, "recorrido"},
    {cmd_segmentos_lista, "segmentos"},
    {cmd_ins_binario, "insertar_binario"},
    {cmd_rmv_binario, "remover_binario"},
    {cmd_flt_binario, "filtrar_binario"},
    {cmd_bsc_subarbol, "buscar_subarbol"},
    {cmd_k_subarbol, "kesimo_subarbol"},

    {cmd_liberar_estructuras, "liberar_estructuras"}};

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

void encolar_enorden(const binario b, cola_binarios &q) {
  if (!es_vacio_binario(b)) {
    encolar_enorden(izquierdo(b), q);
    encolar(b, q);
    encolar_enorden(derecho(b), q);
  }
}

void tiempo_crear_balanceado() {
  const nat MAX = 3000000;
  lista lst = crear_lista();
  for (nat i = 1000000; i < MAX; i++) {
    insertar_despues(crear_info(i, int_a_texto(i)), final_lista(lst), lst);
  }
  printf("Crear balanceado. \n");
  binario bal = crear_balanceado(lst);
  printf("Liberar binario. \n");
  liberar_binario(bal);
  liberar_lista(lst);
}

void tiempo_cnj() {
  lista lst = crear_lista();
  for (int i = 1000000; i <= 1400000; i++) {
    insertar_despues(crear_info(i, int_a_texto(i)), final_lista(lst), lst);
  }
  for (int i = 1700000; i <= 2000000; i++) {
    insertar_despues(crear_info(i, int_a_texto(i)), final_lista(lst), lst);
  }
  conjunto c1 = construir_conjunto(lst);
  liberar_lista(lst);

  lst = crear_lista();
  for (int i = 1200000; i <= 1800000; i++) {
    insertar_despues(crear_info(i, int_a_texto(i)), final_lista(lst), lst);
  }
  conjunto c2 = construir_conjunto(lst);
  liberar_lista(lst);

  printf("  diferencia. \n");
  conjunto d = diferencia(c1, c2);

  texto_t t1 = cadena_a_texto("1000000");
  texto_t t2 = cadena_a_texto("1400000");
  texto_t t3 = cadena_a_texto("1900000");
  assert(pertenece(t1, d) && !pertenece(t2, d) && pertenece(t3, d));

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
  const nat TAMANIO = 1000000;
  printf("  prueba 1. \n");
  cola_de_prioridad cp = crear_cp(TAMANIO);
  for (nat i = TAMANIO; i >= 1; i--) {
    info_t info = crear_info(i, int_a_texto(i));
    insertar_en_cp(info, numero_info(info), cp);
  }
  for (nat i = TAMANIO; i <= 1; i--)
    eliminar_prioritario(cp);

  liberar_cp(cp);

  printf("  prueba 2. \n");
  cp = crear_cp(TAMANIO);
  for (nat i = 1; i <= TAMANIO; i++) {
    info_t info = crear_info(i, int_a_texto(i));
    insertar_en_cp(info, numero_info(info), cp);
  }
  for (nat i = TAMANIO; i <= 1; i--)
    eliminar_prioritario(cp);

  liberar_cp(cp);

  printf("  prueba 3. \n");
  cp = crear_cp(TAMANIO);
  info_t info = crear_info(TAMANIO, int_a_texto(TAMANIO));
  insertar_en_cp(info, numero_info(info), cp);
  for (nat i = 1; i <= TAMANIO; i++) {
    info = crear_info(1, int_a_texto(1));
    insertar_en_cp(info, numero_info(info), cp);
    eliminar_prioritario(cp);
  }
}

int main() {
  lista lst = crear_lista();
  binario b = crear_binario();
  pila p = crear_pila(MAX_PILA);
  cola_binarios q = crear_cola_binarios();
  conjunto c = crear_conjunto();
  cola_de_prioridad cp = crear_cp(MAX_CP);

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
      escribir_nueva_linea();
      break;

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
      liberar_lista(ord);
      imprimir_binario(b);
      break;
    }
    case cmd_por_niveles: {
      escribir_nueva_linea();
      imprimir_textos(b);
      escribir_nueva_linea();
      break;
    }
    case cmd_apilar: {
      texto_t palabra = leer_palabra(MAX_LARGO_PALABRA);
      while (comparar_texto(fin_comando, palabra) != igual) {
        if (!es_llena_pila(p))
          apilar(palabra, p);
        else {
          apilar(palabra, p);
          liberar_texto(palabra);
        }
        palabra = leer_palabra(MAX_LARGO_PALABRA);
      }
      liberar_texto(palabra);
      if (es_llena_pila(p)) {
        palabra = cima(p);
        imprimir_con_nl(palabra);
      }
      break;
    }
    case cmd_desapilar: {
      int cantidad = leer_int();
      for (int i = 1; i < cantidad; i++) {
        if (es_vacia_pila(p)) {
          desapilar(p);
        } else {
          texto_t palabra = cima(p);
          desapilar(p);
          liberar_texto(palabra);
        }
      }
      if (!es_vacia_pila(p)) {
        texto_t palabra = cima(p);
        imprimir_con_nl(palabra);
        desapilar(p);
        liberar_texto(palabra);
      }
      break;
    }
    case cmd_encolar: {
      while (!es_vacia_cola_binarios(q)) {
        desencolar(q);
      }
      encolar_enorden(b, q);
      break;
    }
    case cmd_desencolar: {
      int cantidad = leer_int();
      for (int i = 1; i < cantidad; i++)
        desencolar(q);
      if (!es_vacia_cola_binarios(q)) {
        binario sub = frente(q);
        escribir_nueva_linea();
        imprimir_binario(sub);
        desencolar(q);
      }
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

      conjunto dif = diferencia(cnj, c);
      conjunto inter = interseccion(cnj, c);

      nat cant_dif = 0, cant_inter = 0;
      loc = inicio_lista(otra);
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

    case cmd_tiempo_balanceado: {
      tiempo_crear_balanceado();
      break;
    }
    case cmd_tiempo_cnj: {
      tiempo_cnj();
      break;
    }
    case cmd_tiempo_cp: {
      tiempo_cp();
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
    case cmd_bsc_subarbol: {
      texto_t palabra = leer_palabra(MAX_LARGO_PALABRA);
      binario sub = buscar_subarbol(palabra, b);
      escribir_nueva_linea();
      imprimir_binario(sub);
      liberar_texto(palabra);
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
      liberar_binario(b);
      liberar_pila(p);
      liberar_cola_binarios(q);
      liberar_conjunto(c);
      liberar_cp(cp);

      lst = crear_lista();
      b = crear_binario();
      p = crear_pila(MAX_PILA);
      q = crear_cola_binarios();
      c = crear_conjunto();
      cp = crear_cp(MAX_CP);
      break;
    }

    default:
      imprimir_con_nl(msg_cmd_no_reconocido);
      break;
    } // switch
    texto_t resto_linea = leer_resto_linea(MAX_RESTO_LINEA);
    liberar_texto(resto_linea);
  } // while

  liberar_lista(lst);
  liberar_binario(b);
  liberar_pila(p);
  liberar_cola_binarios(q);
  liberar_conjunto(c);
  liberar_cp(cp);
  return 0;
}
