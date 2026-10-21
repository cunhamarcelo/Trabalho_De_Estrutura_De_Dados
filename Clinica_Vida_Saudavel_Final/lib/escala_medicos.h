#ifndef ESCALA_MEDICOS_H
#define ESCALA_MEDICOS_H

typedef struct no_medico {
    int crm;                    
    struct no_medico *prox;
} NoMedico;

NoMedico *escala_criar();

void escala_destruir(NoMedico **L);

int escala_inserir(NoMedico **L, int crm);

int escala_atual(NoMedico *L);

void escala_avancar(NoMedico **L);

int escala_remover_atual(NoMedico **L);

int escala_tamanho(NoMedico *L);

void escala_imprimir(NoMedico *L);

#endif
