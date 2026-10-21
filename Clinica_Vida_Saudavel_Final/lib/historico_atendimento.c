#include <stdio.h>
#include <stdlib.h>
#include "historico_atendimento.h"

Historico *historico_criar() {
    Historico *H = (Historico*) malloc(sizeof(Historico));
    if (H == NULL) return NULL;
    H->topo = NULL;
    H->tam = 0;
    return H;
}

void historico_destruir(Historico **H) {
    if (H == NULL || *H == NULL) return;
    NoHist *q = (*H)->topo;
    while (q != NULL) {
        NoHist *tmp = q;
        q = q->prox;
        free(tmp);
    }
    free(*H);
    *H = NULL;
}

int historico_empilhar(Historico *H, paciente p, int crm) {
    if (H == NULL) return 0;
    NoHist *novo = (NoHist*) malloc(sizeof(NoHist));
    if (novo == NULL) return 0;

    novo->pessoa = p;
    novo->crm = crm;
    novo->prox = H->topo;
    H->topo = novo;
    H->tam++;
    return 1;
}

int historico_topo(Historico *H, paciente *saida, int *crm) {
    if (H == NULL || H->topo == NULL) return 0;
    if (saida != NULL) *saida = H->topo->pessoa;
    if (crm != NULL)   *crm = H->topo->crm;
    return 1;
}

int historico_desfazer(Historico *H, paciente *saida) {
    if (H == NULL || H->topo == NULL) return 0;
    NoHist *q = H->topo;
    if (saida != NULL) *saida = q->pessoa;
    H->topo = q->prox;
    free(q);
    H->tam--;
    return 1;
}

int historico_vazio(Historico *H) {
    return H == NULL || H->tam == 0;
}

int historico_tamanho(Historico *H) {
    return H == NULL ? 0 : H->tam;
}

void historico_imprimir(Historico *H) {
    if (historico_vazio(H)) {
        printf("Historico vazio\n");
        return;
    }
    int pos = 1;
    for (NoHist *q = H->topo; q != NULL; q = q->prox) {
        printf("%d) %s (tipo %d) - atendido pelo CRM %d%s\n",
               pos++, q->pessoa.nome, q->pessoa.tipo, q->crm,
               (q == H->topo) ? "  <- ultimo atendimento" : "");
    }
}
