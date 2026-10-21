#ifndef PILHA_VETOR_H
#define PILHA_VETOR_H

//Dados
typedef struct {
  int topo, N;
  int *dados;
} Pilha_vet;

#define MAX 100
 
//Fun��es
Pilha_vet* pilha_criar();
void pilha_destruir(Pilha_vet **P);

//Adicionar
void pilha_adicionar(Pilha_vet **P,int x);

//Acessar
int pilha_topo(Pilha_vet *P);

//Remover
void pilha_remover(Pilha_vet **P);

//Extra
int pilha_tamanho(Pilha_vet *P);


#endif

