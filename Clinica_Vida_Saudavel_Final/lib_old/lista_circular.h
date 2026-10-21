#ifndef LISTA_CIRCULAR_H
#define LISTA_CIRCULAR_H

//Dados
typedef struct No {
  int dado;
  struct no *prox;
} No_circ;
 
//Fun��es
No_circ* criar_lista_circ();
void destruir_lista_circ(No_circ **L);

//Imprimir
void imprimir_lista_circ(No_circ *L);

//Adicionar
void adicionar_inicio_circ(No_circ **L, int x);
void adicionar_final_circ(No_circ **L, int x);

//Remover
void remover_inicio_circ(No_circ **L);
void remover_final_circ(No_circ **L);
void remover_valor_circ(No_circ **L, int x);

//Buscar
int buscar_valor_circ(No_circ *L, int x);

//Extra
int tamanho_lista_circ(No_circ *L);

#endif

