#ifndef LISTA_HEAD_H
#define LISTA_HEAD_H

#include "registro_paciente.h"

//Principal estrutura da lista
typedef struct no {
  //id gerado pela função criar_id() em "registro_paciente.h"
  unsigned int id;
  //estrutura paciente criada em "registro_paciente.h"
  paciente pessoa;
  struct no *prox;
} No;
 
//Fun��es
No* criar_lista();
void destruir_lista(No **L);

//Imprimir
void imprimir_lista(No *L);

//Adicionar
void adicionar_final(No *L, paciente x, unsigned int y);

//Remover
void remover_valor(No *L, unsigned int x);

//Buscar
int buscar_valor(No *L, unsigned int x);

#endif
