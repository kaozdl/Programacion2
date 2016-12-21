/* 4580203 - 4660754 */
/*
  Módulo de implementación de 'uso_listas'.

  Laboratorio de Programación 2.
  InCo‐FIng‐UDELAR
 */

#include "../include/utils.h"
#include "../include/texto.h"
#include "../include/info.h"
#include "../include/lista.h"
#include "../include/uso_lista.h"
#include <stdio.h>

// bool esta_ordenada(const lista lst) {
//   bool res = true;
//   if (!es_vacia_lista(lst)) {
//     localizador loc = inicio_lista(lst);
//     while (res && es_localizador_lista(siguiente(loc, lst))) {
//       localizador sig_loc = siguiente(loc, lst);
//       if (numero_info(info_lista(loc, lst)) >
//           numero_info(info_lista(sig_loc, lst)))
//         res = false;
//       else
//         loc = siguiente(loc, lst);
//     }
//   }
//   return res;
// }

bool esta_ordenada(const lista lst) {
  bool res = true;
  if (!es_vacia_lista(lst)) {
    localizador loc = inicio_lista(lst);
    while (res && es_localizador_lista(siguiente(loc, lst))) {
      localizador sig_loc = siguiente(loc, lst);
      if (numero_info(info_lista(loc, lst)) >
          numero_info(info_lista(sig_loc, lst)))
        res = false;
      else
        loc = siguiente(loc, lst);
    }
  }
  return res;
}

// void retroceder(localizador loc, lista &lst) {
//   localizador pto_ins = primer_mayor(loc, lst);
//   mover_antes(pto_ins, loc, lst);
// }

void retroceder(localizador loc, lista &lst) {
  localizador pto_ins = primer_mayor(loc, lst);
  mover_antes(pto_ins, loc, lst);
}


// void unificar(lista &lst) {
//   if (!es_vacia_lista(lst)) {
//     localizador loc = inicio_lista(lst);
//     // se cumplen las precondiciones de `siguiente`
//     localizador sig_loc = siguiente(loc, lst);
//
//     while (es_localizador_lista(sig_loc)) {
//       if (numero_info(info_lista(loc, lst)) ==
//           numero_info(info_lista(sig_loc, lst)))
//         remover_de_lista(sig_loc, lst);
//       else
//         loc = sig_loc;
//       sig_loc = siguiente(loc, lst);
//     }
//   }
// }

void unificar(lista &lst) {
  if (!es_vacia_lista(lst)) {
    localizador loc = inicio_lista(lst);
    // se cumplen las precondiciones de `siguiente`
    localizador sig_loc = siguiente(loc, lst);

    while (es_localizador_lista(sig_loc)) {
      if (numero_info(info_lista(loc, lst)) ==
          numero_info(info_lista(sig_loc, lst)))
        remover_de_lista(sig_loc, lst);
      else
        loc = sig_loc;
      sig_loc = siguiente(loc, lst);
    }
  }
}


//  void cambiar_todos(const int original, const int nuevo, lista &lst) {
//   localizador loc = inicio_lista(lst);
//   while (es_localizador_lista(loc)) {
//     if (numero_info(info_lista(loc, lst)) == original) {
//       info_t info = info_lista(loc, lst);
//       info_t nueva_info = crear_info(nuevo, copiar_texto(texto_info(info)));
//       cambiar_en_lista(nueva_info, loc, lst);
//       // libera la info que no libera cambiar_en_lista
//       liberar_info(info);
//     }
//     loc = siguiente(loc, lst);
//   }
// }

void cambiar_todos(const int original, const int nuevo, lista &lst) {
  localizador loc = inicio_lista(lst);
  while (es_localizador_lista(loc)) {
    if (numero_info(info_lista(loc, lst)) == original) {
      info_t info = info_lista(loc, lst);
      info_t nueva_info = crear_info(nuevo, copiar_texto(texto_info(info)));
      cambiar_en_lista(nueva_info, loc, lst);
      // libera la info que no libera cambiar_en_lista
      liberar_info(info);
    }
    loc = siguiente(loc, lst);
  }
}


// bool pertenece(const int i, const lista lst) {
//   bool esta = false;
// 	if (es_vacia_lista(lst))
//         return esta;
//     else{
//         localizador loc = inicio_lista(lst);
//         while (es_localizador_lista(loc)  && !esta)
// 			if(numero_info(info_lista(loc,lst))==i)
//             	esta = true;
// 			else
// 				loc=siguiente(loc,lst);
//         }
//         return esta;
//     }

bool pertenece(const int i, const lista lst) {
  bool esta = false;
	if (es_vacia_lista(lst))
    return esta;
  else{
    localizador loc = inicio_lista(lst);
    while (es_localizador_lista(loc)  && !esta)
		  if(numero_info(info_lista(loc,lst))==i)
        esta = true;
			else
			   loc=siguiente(loc,lst);
  }
  return esta;
}

nat longitud(const lista lst) {
  localizador lon = inicio_lista(lst);
  nat i=0;
  while (es_localizador_lista(lon)) {
    i++;
    lon = siguiente(lon,lst);
  }
  return i;
}

nat cantidad(const int i, const lista lst) {
  localizador loc = inicio_lista(lst);
  nat contador = 0;
  while(es_localizador_lista(loc)){
    if (numero_info(info_lista(loc,lst))==i)
  	 contador++;
  	loc = siguiente(loc,lst);
  	}
  	return contador;
}

bool son_numeros_iguales(const lista l1, const lista l2) {
  bool iguales = false;
  if ((es_vacia_lista(l1)) && (es_vacia_lista(l2))) {
    iguales = true;
  };
  localizador ll1 = inicio_lista(l1);
  localizador ll2 = inicio_lista(l2);
    while (es_localizador_lista(ll1) && es_localizador_lista(ll2)) {
      if (numero_info(info_lista(ll1,l1))==numero_info(info_lista(ll2,l2))) {
        iguales = true;
      }
      ll1 = siguiente(ll1,l1);
      ll2 = siguiente(ll2,l2);
    }
    return iguales && !es_localizador_lista(ll1)&&!es_localizador_lista(ll2);
}

lista concatenar(const lista l1, const lista l2) {
  lista aux = crear_lista();
  localizador loc1=inicio_lista(l1);
  localizador loc2;
  while (es_localizador_lista(loc1)){
    insertar_despues(info_lista(loc1,l1),loc2,aux);
    loc2=final_lista(aux);
    loc1=siguiente(loc1,l1);
  }
  loc1=inicio_lista(l2);
  while (es_localizador_lista(loc1)){
    insertar_despues(info_lista(loc1,l2),loc2,aux);
    loc2=final_lista(aux);
    loc1=siguiente(loc1,l2);
  }
  return aux;
}

lista reversa(const lista lst) {
  localizador loc = final_lista(lst);
  lista rev = crear_lista ();
  while (es_localizador_lista(loc)) {
    info_t info = info_lista(loc,lst);
    localizador locr = final_lista(rev);
    info_t nuevo_nod = crear_info(numero_info(info),texto_info(info));
    insertar_despues (nuevo_nod, locr, rev);
    loc = anterior(loc,lst);
    }
  return rev;
  }

localizador primer_mayor(const localizador loc, const lista lst) {
  localizador aux =inicio_lista(lst);
  while (aux!=loc && numero_info(info_lista(aux,lst))<=numero_info(info_lista(loc,lst)))
    aux=siguiente(aux,lst);
  return aux;
}

void ordenar(lista &lst) {
  localizador inicio = inicio_lista(lst);
  while (es_localizador_lista(inicio)){
    retroceder(inicio,lst);
    inicio = siguiente(inicio,lst);
  }
}

lista mezcla(const lista l1, const lista l2) {
  localizador localizador1=inicio_lista(l1);
  localizador localizador2=inicio_lista(l2);
  info_t info;
  localizador loc;
  lista mez = crear_lista();
  while(es_localizador_lista(localizador1)&&es_localizador_lista(localizador2)){
    if (numero_info(info_lista(localizador1,l1))<=numero_info(info_lista(localizador2,l2))){
      info=info_lista(localizador1,l1);
      localizador1=siguiente(localizador1,l1);
    }
    else{
      info=info_lista(localizador2,l2);
      localizador2=siguiente(localizador2,l2);
    }
    insertar_despues(info,loc,mez);
    loc=final_lista(mez);
  }
    while(es_localizador_lista(localizador1)){
      info=info_lista(localizador1,l1);
      localizador1=siguiente(localizador1,l1);
      insertar_despues(info,loc,mez);
      loc=final_lista(mez);
    }
    while(es_localizador_lista(localizador2)){
      info=info_lista(localizador2,l2);
      localizador2=siguiente(localizador2,l2);
      insertar_despues(info,loc,mez);
      loc=final_lista(mez);
    }
  return mez;
}

lista filtrado(const int clave, const comp_t criterio, const lista lst) {
  lista fil = crear_lista();
  localizador localizador1 = inicio_lista(lst);
  while(es_localizador_lista(localizador1)){
    bool bandera;
    if (criterio==mayor){
      bandera = numero_info(info_lista(localizador1,lst))>clave;
    }
    else if (criterio==igual){
      bandera = numero_info(info_lista(localizador1,lst))==clave;
    }
          else {
            bandera = numero_info(info_lista(localizador1,lst))<clave;
          }
    if (bandera){
      localizador final =final_lista(fil);
      info_t info_auxiliar = info_lista(localizador1,lst);
      insertar_despues(info_auxiliar,final,fil);
    }
    localizador1=siguiente(localizador1,lst);
  }
  return fil;
}

lista sublista(const nat menor, const nat mayor, const lista lst) {
  int may = mayor;
  int men = menor;
  lista sub = crear_lista();
  localizador localizador1 = inicio_lista(lst);
  while(es_localizador_lista(localizador1)){
      if (((numero_info(info_lista(localizador1,lst)))<=may) &&  ((numero_info(info_lista(localizador1,lst)))>=men)){
          info_t info2 = info_lista(localizador1,lst);
          localizador ultimo =final_lista(sub);
          insertar_despues(info2,ultimo,sub);
      }
      localizador1=siguiente(localizador1,lst);
  }
  return sub;
}

void imprimir_lista(const lista lst) {
  localizador localizador1 = inicio_lista(lst);
  while (es_localizador_lista(localizador1)){
  printf("(%d,",numero_info(info_lista(localizador1,lst)));
      escribir_texto(texto_info(info_lista(localizador1,lst)));
      printf(")");
      localizador1 = siguiente(localizador1,lst);
  }
  printf("\n");
}
