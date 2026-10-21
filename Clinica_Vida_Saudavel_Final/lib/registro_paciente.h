#ifndef REGISTRO_PACIENTE_H
#define REGISTRO_PACIENTE_H

#include "lista_com_cabeca.h"

typedef struct paciente{
    char nome[100];
    int tipo;
} paciente;

//estrutura No da lib "lista_com_cabeca.h"
typedef struct no No;

No *criar_registro_pacientes();

void adicionar_paciente(No* x, const char *y, int z);

void excluir_paciente(No* x, unsigned int y);

void imprimir_lista_paciente(No* x);

unsigned int criar_id(const char *x);

No *pesquisar_paciente(No* x, unsigned int y);

#endif
