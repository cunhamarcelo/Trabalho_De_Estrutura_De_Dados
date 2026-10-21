#include "lista_com_cabeca.h"
#include <stdlib.h>
#include <stdio.h>

No* criar_lista() {
  No *q = (No*) malloc(sizeof(No));
  q->prox = NULL;
return q; 
} 

void destruir_iterativo(No **p) { //vers�o iterativa
  No *q;
  while(*p != NULL){
    q = *p;
    *p = (*p)->prox;
    free(q);
  }
}

void destruir_recursivo(No *p) { //vers�o recursiva
  if (p != NULL) {
    destruir_recursivo(p->prox);
    free(p);
  }
}

void destruir_lista(No **p){
  destruir_iterativo(p);
  //destruir_recursivo(*p); *p = NULL;
}


void adicionar_final(No *p, paciente x, unsigned int y) {// p recebe L
  No *q, *aux;
  q = (No*) malloc(sizeof(No));
  q->id = y;
  q->pessoa = x;
  q->prox = NULL;
  aux = p;
  while (aux->prox != NULL){
    aux = aux->prox;
  }
  
  aux->prox = q;
}

//Imprimir

void imprimir_lista(No *p) { //vers�o iterativa
  No* q;
  for (q = p->prox; q != NULL; q = q->prox){ 
    printf("Nome:%s/nId:%u/nTipo de Atendimento:%d/n''/n",q->pessoa.nome, q->id, q->pessoa.tipo);
  }
  printf("NULL\n");
}

//Buscar
int buscar_valor(No *p, unsigned int x) {// q recebe L
  p = p->prox;
  while(p != NULL){
    if(p->id == x) return 1; //true!
    p = p->prox;
  }
  return 0;//false == n�o encontrou
}


void remover_valor(No *p,unsigned int v) {
    No *q = p;
    while (q->prox != NULL) {
        if (q->prox->id == v) {
            No *tmp = q->prox;
            q->prox = tmp->prox;   
            free(tmp);
            return;                
        }
        q = q->prox;               
    }

}

