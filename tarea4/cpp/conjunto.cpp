/* 4580203 - 4660754 */


#include "../include/utils.h"
#include "../include/texto.h"
#include "../include/info.h"
#include "../include/lista.h"
#include "../include/binario.h"
#include "../include/pila.h"
#include "../include/cola_binarios.h"
#include "../include/conjunto.h"
#include "../include/cola_de_prioridad.h"

#include <stdlib.h>

struct rep_conjunto {
  binario bin;
};
typedef rep_conjunto *conjunto;

conjunto crear_conjunto(){
    conjunto c = new rep_conjunto;
    c->bin = crear_binario();
    return c;
}

conjunto construir_conjunto(const lista lst){
  conjunto c = new rep_conjunto;
  c->bin = crear_balanceado(lst);
  return c;
}

bool incluir(const info_t i, conjunto &c) {
  return insertar_en_binario(i,c->bin);
}

void excluir(const texto_t t, conjunto &c){
    remover_de_binario(t,c->bin);
}


lista diferencia_de_listas(const lista lst1, const lista lst2){
    localizador localizador1 = inicio_lista(lst1);
    localizador localizador2 = inicio_lista(lst2);
    lista dif = crear_lista();
    localizador loc;
    loc = NULL;

    while (es_localizador_lista(localizador1)&&es_localizador_lista(localizador2)) {
        comp_t comp = comparar_texto(texto_info(info_lista(localizador1,lst1)),texto_info(info_lista(localizador2,lst2)));
        if (comp == igual){
            localizador1 = siguiente(localizador1,lst1);
            localizador2 = siguiente(localizador2,lst2);
        }
        else if (comp == menor){
            loc = final_lista(dif);
            info_t info=info_lista(localizador1,lst1);
            info_t info_auxiliar = crear_info(numero_info(info), copiar_texto(texto_info(info)));
            insertar_despues(info_auxiliar,loc,dif);
            localizador1 = siguiente(localizador1,lst1);
        }
        else localizador2 = siguiente(localizador2,lst2);
    }
    while(es_localizador_lista(localizador1)){
        loc=final_lista(dif);
        info_t info=info_lista(localizador1,lst1);
        info_t info_auxiliar = crear_info(numero_info(info), copiar_texto(texto_info(info)));
        insertar_despues(info_auxiliar,loc,dif);
        localizador1=siguiente(localizador1,lst1);
    }
    return dif;

}
conjunto diferencia(const conjunto c1, const conjunto c2){
    lista lst1 = linealizacion(c1->bin);
    lista lst2 = linealizacion (c2->bin);
    lista inter = diferencia_de_listas(lst1,lst2);
    conjunto binter = crear_conjunto();
    binter->bin = crear_balanceado(inter);
    return binter;
}




lista interseccion_de_listas(const lista lst1, const lista lst2){
    localizador localizador1 = inicio_lista(lst1);
    localizador localizador2 = inicio_lista(lst2);
    lista in = crear_lista();
    localizador loc;
    loc = NULL;

    while (es_localizador_lista(localizador1)&&es_localizador_lista(localizador2)) {
        comp_t comp = comparar_texto(texto_info(info_lista(localizador1,lst1)),texto_info(info_lista(localizador2,lst2)));
        if (comp == igual){
            loc = final_lista(in);
            info_t info=info_lista(localizador1,lst1);
            info_t info_auxiliar = crear_info(numero_info(info), copiar_texto(texto_info(info)));
            insertar_despues(info_auxiliar,loc,in);
            localizador1 = siguiente(localizador1,lst1);
            localizador2 = siguiente(localizador2,lst2);
        }
        else if (comp == menor)
         localizador1 = siguiente(localizador1,lst1);
            else
             localizador2 = siguiente(localizador2,lst2);


        }
    return in;
}


conjunto interseccion(const conjunto c1, const conjunto c2){
    lista lst1 = linealizacion(c1->bin);
    lista lst2 = linealizacion(c2->bin);
    lista inter = interseccion_de_listas(lst1,lst2);
    conjunto binter = crear_conjunto();
    binter->bin = crear_balanceado(inter);
    return binter;
}

bool pertenece(const texto_t t, const conjunto c){
 return (!es_vacio_binario(buscar_subarbol(t,c->bin)));
}

bool es_vacio_conjunto(const conjunto c){
  return es_vacio_binario(c->bin);
}

void liberar_conjunto(conjunto &c){
    c=NULL;
}
