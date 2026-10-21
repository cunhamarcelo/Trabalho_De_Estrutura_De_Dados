#ifndef FILA_HOSPITAL_H
#define FILA_HOSPITAL_H
#include "lista_com_cabeca.h"
#include "registro_paciente.h"

#define TIPO_NORMAL       1
#define TIPO_PREFERENCIAL 2
#define TIPO_EMERGENCIAL  3

typedef struct no_fila {
    unsigned int id;        
    paciente pessoa;        
    struct no_fila *prox;
} NoFila;

typedef struct {
    NoFila *ini;
    NoFila *fim;
    int tam;                
} FilaHospital;
 
FilaHospital *fila_hospital_criar();
void fila_hospital_destruir(FilaHospital **F);

int fila_hospital_enfileirar(FilaHospital *F, const char *nome, int tipo);

int fila_hospital_enfileirar_registro(FilaHospital *F, No *registro, unsigned int id);

int fila_hospital_proximo(FilaHospital *F, paciente *saida);

int fila_hospital_atender(FilaHospital *F, paciente *saida);

// Retorna 1 se ja existe paciente com esse id (mesmo nome) na fila, 0 caso contrario
int fila_hospital_contem(FilaHospital *F, unsigned int id);

int fila_hospital_vazia(FilaHospital *F);
int fila_hospital_tamanho(FilaHospital *F);

void fila_hospital_imprimir(FilaHospital *F);

#endif
