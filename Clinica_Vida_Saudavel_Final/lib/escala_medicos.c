#include <stdio.h>
#include <stdlib.h>
#include "escala_medicos.h"

NoMedico *escala_criar() {
    return NULL;
}

void escala_destruir(NoMedico **L) {
    if (L == NULL || *L == NULL) return;
    NoMedico *ultimo = *L;
    NoMedico *q = ultimo->prox;

    while (q != ultimo) {
        NoMedico *tmp = q;
        q = q->prox;
        free(tmp);
    }

    free(ultimo);
    *L = NULL;
}

int escala_inserir(NoMedico **L, int crm) {
    if (L == NULL) return 0;
    if (*L != NULL) {
        NoMedico *q = (*L)->prox;
        do {
            if (q->crm == crm) return 0;
            q = q->prox;
        } while (q != (*L)->prox);
    }

    NoMedico *novo = (NoMedico*) malloc(sizeof(NoMedico));

    if (novo == NULL) return 0;
    novo->crm = crm;

    if (*L == NULL) {                         
        novo->prox = novo;
    } else {                                  
        novo->prox = (*L)->prox;
        (*L)->prox = novo;
    }

    *L = novo;                               
    return 1;
}

int escala_atual(NoMedico *L) {
    if (L == NULL) return -1;
    return L->prox->crm;
}

void escala_avancar(NoMedico **L) {
    if (L == NULL || *L == NULL) return;
    *L = (*L)->prox;
}

int escala_remover_atual(NoMedico **L) {
    if (L == NULL || *L == NULL) return 0;

    NoMedico *ultimo = *L;
    NoMedico *primeiro = ultimo->prox;

    if (primeiro == ultimo) {    
        free(primeiro);
        *L = NULL;
        return 1;
    }

    ultimo->prox = primeiro->prox;
    free(primeiro);
    return 1;
}

int escala_tamanho(NoMedico *L) {
    if (L == NULL) return 0;
    int n = 0;
    NoMedico *q = L->prox;
    
    do {
        n++;
        q = q->prox;
    } while (q != L->prox);
    return n;
}

void escala_imprimir(NoMedico *L) {
    if (L == NULL) {
        printf("Escala vazia\n");
        return;
    }

    NoMedico *q = L->prox;
    int pos = 1;

    do {
        printf("%d) CRM %d%s\n", pos++, q->crm, (q == L->prox) ? "  <- da vez" : "");
        q = q->prox;
    } while (q != L->prox);
}
