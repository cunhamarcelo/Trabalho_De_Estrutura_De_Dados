#ifndef HISTORICO_ATENDIMENTO_H
#define HISTORICO_ATENDIMENTO_H

#include "lista_com_cabeca.h"
#include "registro_paciente.h"

typedef struct no_hist {
    paciente pessoa;
    int crm;
    struct no_hist *prox;
} NoHist;

typedef struct {
    NoHist *topo;
    int tam;
} Historico;

Historico *historico_criar();
void historico_destruir(Historico **H);

int historico_empilhar(Historico *H, paciente p, int crm);

int historico_topo(Historico *H, paciente *saida, int *crm);

int historico_desfazer(Historico *H, paciente *saida);

int historico_vazio(Historico *H);
int historico_tamanho(Historico *H);

void historico_imprimir(Historico *H);

#endif
