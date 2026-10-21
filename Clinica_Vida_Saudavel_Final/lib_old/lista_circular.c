#include "lista_circular.h"
#include <stdlib.h>
#include <stdio.h>

No_circ* criar_lista_circ() {
  return NULL; 
} 

void destruir_lista_circ(No_circ **p) {//versao iterativa
  if(*p == NULL) return;// lista vazia
  No_circ *q = (*p)->prox, *aux;
  while(q != *p){
    aux = q;
    q = q->prox;
    free(aux);
  }
  free(*p);
  *p = NULL;
}

//Inserção

void adicionar_inicio_circ(No_circ** p, int x){//p recebe |$\&$|L
  No_circ *q = (No_circ*) malloc(sizeof(No_circ));
  q->dado = x;
  if(*p == NULL){ //lista vazia
    *p = q;
    q->prox = q;
  }
  else{
    q->prox = (*p)->prox;
    (*p)->prox = q;
  }
}

void adicionar_final_circ(No_circ **p, int x) {// p recebe L
  No_circ *q = (No_circ*) malloc(sizeof(No_circ));
  q->dado = x;
  if(*p == NULL){ //lista vazia
    *p = q;
    q->prox = q;
  }
  else{
    q->prox = (*p)->prox;
    (*p)->prox = q;
    *p = q;
  }
}

//Imprimir

void imprimir_lista_circ(No_circ *p) { // p recebe L
  No_circ* q, *aux = p;
  if(p!=NULL){
    for (q = p->prox; q != aux; q = q->prox) printf("%d -> ", q->dado);
    printf("%d -> ", q->dado);
  }
  printf("NULL\n");
}

//Buscar
int buscar_valor_circ(No_circ *p, int x) {// q recebe L
  if(p==NULL) return -1; //lista vazia
  No_circ *q = p;
  p = p->prox;
  while(p != q){
    if(p->dado == x) return 1; //true!
      p = p->prox;
  }
  if(p->dado == x) return 1; //true!
  return 0;//false == n�o encontrou
}

//Remoção

void remover_inicio_circ(No_circ **p) {// p recebe L
  if(*p==NULL) return; //lista vazia
  No_circ* q = *p; 
  if(q->prox==q){//1 único nó
    free(q); *p = NULL;
    return;
  }    
  q = q->prox;  
  (*p)->prox = q->prox;
  free(q);
}
  
void remover_final_circ(No_circ **p) {// p recebe L
  if(*p==NULL) return; //lista vazia
  No_circ* q = *p; 
  if(q->prox==q){//1 único nó
    free(q); *p = NULL;
    return;
  }    
  No_circ *aux = q;
  while(q->prox != aux) q = q->prox;  
  q->prox = aux->prox;
  *p = q;
  free(aux);
}

void remover_valor_circ(No_circ **p, int x) {// p recebe |$\&$|L
  if(*p==NULL) return; //lista vazia
  No_circ *q = *p;
  if(q->prox == q && q->dado == x){//1 único nó
    free(q); *p = NULL;
    return;
  }
  while(q->prox != *p && (q->prox)->dado != x) q = q->prox;
  if((q->prox)->dado == x){//encontrou
    No_circ *aux = q->prox;
    q->prox = aux->prox;
    if(*p == aux)//último elemento
      *p = q;
    free(aux);
  }
}

int tamanho_lista_cric(No_circ *p){
  if(p==NULL) return 0; //lista vazia
  No_circ *q = p; 
  int tam=1;
  for(p = p->prox; p != q; p = p->prox) tam++;
  return tam;
}
























//
