#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila_hospital.h"

int fila_hospital_contem(FilaHospital *F, unsigned int id) {
    if (F == NULL) return 0;
    for (NoFila *q = F->ini; q != NULL; q = q->prox)
        if (q->id == id) return 1;
    return 0;
}

static int inserir_no(FilaHospital *F, unsigned int id, paciente p) {
    if (p.tipo < TIPO_NORMAL || p.tipo > TIPO_EMERGENCIAL) return 0;
    if (fila_hospital_contem(F, id)) return 0;   /* nao permite nome repetido na fila */

    NoFila *novo = (NoFila*) malloc(sizeof(NoFila));
    if (novo == NULL) return 0;

    novo->id = id;
    novo->pessoa = p;
    novo->prox = NULL;

    if (F->fim == NULL)
        F->ini = novo;
    else
        F->fim->prox = novo;
    F->fim = novo;

    F->tam++;
    return 1;
}

FilaHospital *fila_hospital_criar() {
    FilaHospital *F = (FilaHospital*) malloc(sizeof(FilaHospital));
    if (F == NULL) return NULL;
    F->ini = NULL;
    F->fim = NULL;
    F->tam = 0;
    return F;
}

void fila_hospital_destruir(FilaHospital **F) {  /* recebe &F */
    if (F == NULL || *F == NULL) return;
    NoFila *q = (*F)->ini;
    while (q != NULL) {
        NoFila *tmp = q;
        q = q->prox;
        free(tmp);
    }
    free(*F);
    *F = NULL;
}

int fila_hospital_enfileirar(FilaHospital *F, const char *nome, int tipo) {
    if (F == NULL || nome == NULL) return 0;

    paciente p = {0};
    p.tipo = tipo;
    strncpy(p.nome, nome, sizeof(p.nome) - 1);

    return inserir_no(F, criar_id(nome), p);
}

int fila_hospital_enfileirar_registro(FilaHospital *F, No *registro, unsigned int id) {
    if (F == NULL || registro == NULL) return 0;

    for (No *q = registro->prox; q != NULL; q = q->prox) {
        if (q->id == id)
            return inserir_no(F, q->id, q->pessoa);
    }
    return 0; 
}

int fila_hospital_proximo(FilaHospital *F, paciente *saida) {
    if (F == NULL || F->ini == NULL) return 0;
    if (saida != NULL) *saida = F->ini->pessoa;
    return 1;
}

int fila_hospital_atender(FilaHospital *F, paciente *saida) {
    if (F == NULL || F->ini == NULL) return 0;

    NoFila *q = F->ini;
    if (saida != NULL) *saida = q->pessoa;

    F->ini = q->prox;
    if (F->ini == NULL)
        F->fim = NULL;

    free(q);
    F->tam--;
    return 1;
}

int fila_hospital_vazia(FilaHospital *F) {
    return F == NULL || F->tam == 0;
}

int fila_hospital_tamanho(FilaHospital *F) {
    return F == NULL ? 0 : F->tam;
}

void fila_hospital_imprimir(FilaHospital *F) {
    if (fila_hospital_vazia(F)) {
        printf("Fila vazia\n");
        return;
    }
    int pos = 1;
    for (NoFila *q = F->ini; q != NULL; q = q->prox) {
        printf("%d) Id: %u | Nome: %s | Tipo: %d\n",
               pos++, q->id, q->pessoa.nome, q->pessoa.tipo);
    }
}
