/* 4580203 - 4660754 */
#include "../include/texto.h"
#include "../include/info.h"
#include "../include/lista.h"
#include "../include/uso_lista_arboles.h"
#include "../include/finitario.h"

#include <stdlib.h>

struct rep_finitario {
  info_t dato;
  rep_finitario *primer_hijo;
  rep_finitario *sig_hermano;
};

//AUXILIARES DE FINITARIO
//Devuelve el Maximo entre dos numeros naturales.
nat max2 (const nat a, const nat b){
  if (a < b) return b;
  else return a;
}
//Devuelve true si el finitario f es hoja y false en caso contrario.
bool es_hoja (const finitario f) {
  if ((f->primer_hijo == NULL) && (f->sig_hermano == NULL)) return true;
  else return false;
}


finitario crear_finitario() {
  finitario fin = NULL;
  return fin;
}

void insertar_en_finitario(const info_t i, const nat k, finitario &f) {
  finitario insertar = new rep_finitario;
    insertar->dato=i;
    insertar->primer_hijo=NULL;
    if (f==NULL){
        f=insertar;
        f->sig_hermano=NULL;
    }

    else if (f->primer_hijo==NULL && k!= 1) {
        f->primer_hijo=insertar;
        insertar->sig_hermano=NULL;
    }
    else {
        finitario resto = f->primer_hijo;

        for (nat i = 1; i<k-1 && resto->sig_hermano!=NULL;i++){
           resto = resto->sig_hermano;

        }
        if (k!=1){
        insertar->sig_hermano=resto->sig_hermano;
        resto->sig_hermano=insertar;
      }
       else {
       insertar->sig_hermano=f->primer_hijo;
       f->primer_hijo=insertar;

       }
}
}

void liberar_finitario(finitario &f) {
  if (f!=NULL){
       liberar_finitario(f->primer_hijo);
       liberar_finitario(f->sig_hermano);
       liberar_info(f->dato);
       delete f;
       f=NULL;
    }
}

bool es_vacio_finitario(const finitario f) {
  return (f == NULL);
}

info_t raiz_finitario(const finitario f) {
  return f->dato;
}

finitario hijo(const nat k, const finitario f) {
    if (k==1)
        return f->primer_hijo;
    else if (f->primer_hijo!=NULL){
        finitario son = f->primer_hijo;
        for (nat i = 1; i < k && son!=NULL; i++) {
          son = son->sig_hermano;
        }

        return son;
    }
    else return NULL;
  }

void nivel_aux(lista &lst, const nat k, const finitario f){
  if (f != NULL){
    localizador loc1 = final_lista(lst);
    if (k == 1){
      info_t info = crear_info(numero_info(f->dato), copiar_texto(texto_info(f->dato)));
      insertar_despues(info,loc1,lst);
      loc1 = final_lista(lst);
      nivel_aux(lst,k,f->sig_hermano);
    }
    else {
      nivel_aux(lst,k-1,f->primer_hijo);
      nivel_aux(lst,k,f->sig_hermano);

    }
  }
}

lista nivel(nat k, const finitario f) {
  lista niv = crear_lista();
  nivel_aux(niv,k,f);
  ordenar(niv);
  return niv;
}

nat altura_finitario(const finitario f) {
  if (es_vacio_finitario(f)) return 0;
  else
    return (max2(1+altura_finitario(f->primer_hijo),(altura_finitario(f->sig_hermano))));
  }
